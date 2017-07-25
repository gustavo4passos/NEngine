#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <vector>
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
  // Create a sound source, with a 3D position
  int createSource(float gain = 1.f, float pitch = 1.f, bool looping = false, float x = 0.f, float y = 0.f, float z = 0.f);
  // Play loaded audio
  void play(int source, int buffer);

  // Position a source in 3D space
  void sourcePosition(int source, float x = 0.f, float y = 0.f, float z = 0.f);

  // Clean loaded data
  void clean();

private:
  AudioEngine();
  ~AudioEngine();
  static AudioEngine* _instance;

  // Store sources
  std::vector<ALuint> _sources;
  std::vector<ALuint> _buffers;

};

#endif
