#include "AudioEngine.h"
#include <stdio.h>
#include <SDL2/SDL.h>

// Set the static instance to 0
AudioEngine* AudioEngine::_instance = 0;

AudioEngine::AudioEngine()
{ }
AudioEngine::~AudioEngine()
{
  delete _instance;
}

int AudioEngine::loadWAV(const char* path, bool stereo, unsigned int format8or16)
{
  SDL_AudioSpec spec;
  Uint32 wavLength;
  Uint8* wavBuffer;

  // Load file and check for errors. If unable to load correctly, returns -1;
  if(SDL_LoadWAV(path, &spec, &wavBuffer, &wavLength) == NULL)
  {
    printf("AUDIO ENGINE ERROR: Unable to load wav file: %s. Error: %s\n", SDL_GetError());
    return -1;
  }

  // Decides audio format based on arguments
  ALenum format;
  if(stereo)
  {
    format = (format8or16 == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
  }
  else
  {
    format = (format8or16 == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
  }

  ALuint buffer;
  alGenBuffers(1, &buffer);
  alBufferData(buffer, format, wavBuffer, wavLength, spec.freq);

  SDL_FreeWAV(wavBuffer);

  ALenum error = alGetError();
  if(error != AL_NO_ERROR)
  {
    printf("AUDIO ENGINE ERROR: OpenAL error: Could not load audio buffer. Error code: %i\n", error);
    SDL_FreeWAV(wavBuffer);
    return -1;
  }

  // Push buffer into vector
  _buffers.push_back(buffer);
  int position = _buffers.size() - 1;
  return position;
}

void AudioEngine::play(int source, int buffer)
{
  // Check if buffer are inside the buffers scope
  if(buffer < 0 || buffer > (_buffers.size() - 1))
  {
    printf("AUDIO ENGINE ERROR: Invalid buffer.\n");
  }
  // Check if source are inside the sources scope
  else if(source < 0 || source > (_sources.size() - 1))
  {
    printf("AUDIO ENGINE ERROR: Invalid source.\n");
  }
  else
  {
    alSourcei(_sources[source], AL_BUFFER, _buffers[buffer]);
    alSourcePlay(_sources[source]);
  }
}

int AudioEngine::createSource(float gain, float pitch, bool looping, float x, float y, float z)
{
  // Generate source
  ALuint source;
  alGenSources(1, &source);

  // Check for errors
  ALenum error = alGetError();
  if(error != AL_NO_ERROR)
  {
    printf("AUDIO ENGINE ERROR: Unable to create source. Error code: %i\n", error);
    return -1;
  }
  else
  {
    // Set up the source position
    alSourcef(source, AL_PITCH, pitch);
    alSourcef(source, AL_GAIN, gain);
    alSource3f(source, AL_VELOCITY, 0.f, 0.f, 0.f);
    alSource3f(source, AL_POSITION, x, y, z);
    // Set up if the source is loopin based on argument
    ALenum looping = (looping) ? AL_TRUE : AL_FALSE;
    alSourcei(source, AL_LOOPING, looping);

    // Push source back into vector and return position
    _sources.push_back(source);
    int position = _sources.size() - 1;
    return position;
  }
}

void AudioEngine::sourcePosition(int source, float x, float y, float z)
{
  if(source < 0 || source > (_sources.size() -1 ))
  {
    printf("AUDIO ENGINE ERROR: Unable to change sources position. Invalid source.\n");
  }
  else
  {
    alSource3f(_sources[source], AL_POSITION, x, y, z);
  }
}

// Clean data
void AudioEngine::clean()
{
  for(std::vector<ALuint>::iterator it = _buffers.begin(); it != _buffers.end(); it++)
  {
    alDeleteSources(1, &*it);
  }
  _buffers.clear();

  for(std::vector<ALuint>::iterator it = _sources.begin(); it != _sources.end(); it++)
  {
    alDeleteSources(1, &*it);
  }
  _sources.clear();
}
