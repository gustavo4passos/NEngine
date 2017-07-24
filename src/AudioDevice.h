#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <al.h>
#include <alc.h>

class AudioDevice
{
public:
  AudioDevice();

private:
  ALCdevice* _audioDevice;
  ALCcontext* _audioContext;
};

#endif
