#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <vector>
#include <string>
#include "AudioDevice.h"

class AudioEngine
{
public:
  static AudioEngine* instance()
  {
    if(_instance == 0)
    {
      _instance = new AudioEngine();
    }
    return _instance;
  }

  // Load a buffer and return it's position on the buffer array
  int loadWAV(const char* path, bool stereo, unsigned int format8or16);
  int loadMP3(const char* path);

  // Create a sound source, with a 3D position. Returns -1 if unable to createe source
  int createSource(float gain = 1.f, float pitch = 1.f, bool looping = false, float x = 0.f, float y = 0.f, float z = 0.f);
  void deleteSource(int source);
  void deleteBuffer(int buffer);

  // Play loaded audio
  void play(int source, int buffer);
  void stop(int source);

  // Position a source in 3D space
  void sourcePosition(int source, float x = 0.f, float y = 0.f, float z = 0.f);

  // Get string error from ALenum
  std::string getErrorString(ALenum error);
  // Clean loaded data
  void clean();

private:
  AudioEngine();
  ~AudioEngine();
  static AudioEngine* _instance;

  // Store sources
  // FIXME this is gonna lead to problems. Using an array position is not reliable because if a source of buffer is deleted the positions change
  std::vector<ALuint> _sources;
  std::vector<ALuint> _buffers;

};

#endif
