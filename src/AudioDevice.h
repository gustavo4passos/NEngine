#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <al.h>
#include <alc.h>

class AudioDevice
{
public:
  AudioDevice();

  bool initializationStatus() const { return _initializationStatus; }

private:
  ALCdevice* _audioDevice;
  ALCcontext* _audioContext;

  // Stores the initialization status (true = successfully initialized, false otherwise)
  bool _initializationStatus;
};

#endif
