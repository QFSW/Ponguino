// Based off the following experiment
// https://github.com/bitbank2/oled_turbo

#pragma once

#include <inttypes.h>

#define I2CPORT PORTC
#define I2CDDR DDRC

// Pin or port numbers for SDA and SCL
#define BB_SDA 4
#define BB_SCL 5

namespace fast_i2c
{
    void begin(uint8_t addr);
    void end();
    void write(const uint8_t* data, int len);

    void byte_out(uint8_t byte);
}