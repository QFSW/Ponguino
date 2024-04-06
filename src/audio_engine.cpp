#include "audio_engine.h"

#include <Arduino.h>

// Include the codegen from ArduinoMIDI
#include "track_codegen.h"

void AudioEngine::start()
{
    _curr_note_index = 0;
    _curr_note_remaining = decompress_duration(0);

    const uint16_t frequency = decompress_frequency(0);
    play_tone(frequency);
}

void AudioEngine::tick()
{
    long const timeNow = millis();
    long const elapsedTime = timeNow - _last_tick;
    _curr_note_remaining -= elapsedTime;

    // Keep advacing to next note if current one is done
    if (_curr_note_remaining <= 0)
    {
        _curr_note_index++;
        if (_curr_note_index >= NUM_NOTES)
        {
            _curr_note_index = 0;
        }

        _curr_note_remaining += decompress_duration(_curr_note_index);
        const uint16_t frequency = decompress_frequency(_curr_note_index);
        play_tone(frequency);
    }

    _last_tick = timeNow;
}

void AudioEngine::play_tone(uint16_t frequency)
{
    if (frequency == 0)
    {
        noTone(AUDIO_PIN);
        digitalWrite(AUDIO_PIN, LOW);
    }
    else
    {
        tone(AUDIO_PIN, frequency);
    }
}

uint16_t AudioEngine::decompress_frequency(int note_index) const
{
    const uint32_t bitIndex = note_index * BITS_PER_SEMITONE;
    const uint32_t semitoneIndex = decompress(compressedSemitones, bitIndex, BITS_PER_SEMITONE);

    return pgm_read_word(semitoneFrequencyTable + semitoneIndex);
}

uint16_t AudioEngine::decompress_duration(int note_index) const
{
    const uint32_t bitIndex = note_index * BITS_PER_DURATION;
    const uint32_t durationIndex = decompress(compressedDurations, bitIndex, BITS_PER_DURATION);

    return pgm_read_word(durationMsTable + durationIndex);
}

uint16_t AudioEngine::decompress(const uint8_t* buffer, uint32_t bitIndex, uint8_t numBits) const
{
    uint16_t result = 0;
    uint8_t writeBit = 0;

    uint8_t remainingBits = numBits;
    uint32_t bitReadHead = bitIndex;

    while (remainingBits > 0)
    {
        uint32_t const byteToRead = bitReadHead >> 3; //  x / 8
        uint8_t const readBit = bitReadHead & 0b111; // x % 8;
        uint8_t const bitsToRead = min(8 - readBit, remainingBits);

        uint32_t const readMask = (1 << bitsToRead) - 1; // 2 ^ x - 1;
        uint32_t const fullByte = pgm_read_byte(buffer + byteToRead);
        uint32_t const extractedVal = ((fullByte >> readBit) & readMask);

        result |= (extractedVal << writeBit);

        writeBit += bitsToRead;
        remainingBits -= bitsToRead;
        bitReadHead += bitsToRead;
    }
    
    return result;
}