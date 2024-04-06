#pragma once

#include <inttypes.h>

#define AUDIO_PIN 8

class AudioEngine
{
public:
    void start();
    void tick();

private:
    void play_tone(uint16_t frequency);

    uint16_t decompress_frequency(int note_index) const;
    uint16_t decompress_duration(int note_index) const;

    uint16_t decompress(const uint8_t* buffer, uint32_t bitIndex, uint8_t numBits) const;

    int _curr_note_index;
    long _curr_note_remaining;
    long _last_tick;
};