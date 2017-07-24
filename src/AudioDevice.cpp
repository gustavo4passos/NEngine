#include <stdio.h>
#include "AudioDevice.h"


AudioDevice::AudioDevice() : _audioDevice(NULL), _audioContext(NULL)
{
  // Open the first audio device available
  _audioDevice = alcOpenDevice(NULL);
  // Checks if the audio device was opened successfully
  if(!_audioDevice)
  {
    ALenum error = alGetError();
    printf("OPENAL ERROR: Unable to open audio device. Error: %i\n", error);
    _initializationStatus = false;
  }
  else
  {
    // Creates an audio context and makes it current
    _audioContext = alcCreateContext(_audioDevice, NULL);
    alcMakeContextCurrent(_audioContext);
    // Checks for erros
    if(!_audioContext)
    {
      ALenum error = alcGetError(_audioDevice);
      printf("OPENGL ERROR: Unable to create audio context. Error: %s\n", error);
      _initializationStatus = false;
    }
    else
    {

        printf("OPENAL: Audio device successfully initialized.\n");
        _initializationStatus = true;

        // Setting up the listener position (Default: Center of the screen);
        alListener3f(AL_POSITION, 0.f, 0.f, 1.0);
        alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f);
        ALfloat listenerOrientation[] = { 0.f, 0.f, 1.f, 0.f, 1.f, 0.f};
        alListenerfv(AL_ORIENTATION, listenerOrientation);
    }
  }
}
