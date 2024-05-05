// Based off the following experiment
// https://github.com/bitbank2/oled_turbo

#include "fast_i2c.h"
#include <Arduino.h>

#define I2C_CLK_LOW() I2CPORT &= ~(1 << BB_SCL) //compiles to cbi instruction taking 2 clock cycles, extending the clock pulse

namespace fast_i2c
{
    void begin(uint8_t addr)
    {
        I2CPORT |= ((1 << BB_SDA) + (1 << BB_SCL));
        I2CDDR |= ((1 << BB_SDA) + (1 << BB_SCL));
        I2CPORT &= ~(1 << BB_SDA); // data line low first
        I2CPORT &= ~(1 << BB_SCL); // then clock line low is a START signal
        byte_out(addr << 1); // send the slave address
    }

    void end()
    {
        I2CPORT &= ~(1 << BB_SDA);
        I2CPORT |= (1 << BB_SCL);
        I2CPORT |= (1 << BB_SDA);
        I2CDDR &= ~((1 << BB_SDA) | (1 << BB_SCL)); // let the lines float (tri-state)
    }

    void write(const uint8_t* data, int len)
    {
        uint8_t byteOld = I2CPORT & ~((1 << BB_SDA) | (1 << BB_SCL));

        while (len--)
        {
            uint8_t byteCurr = *data++;
            if (byteCurr == 0 || byteCurr == 0xFF) // special case can save time
            {
                byteOld &= ~(1 << BB_SDA);
                if (byteCurr & 0x80)
                {
                    byteOld |= (1 << BB_SDA);
                }

                I2CPORT = byteOld;
                for (uint8_t bitIndex = 0; bitIndex < 8; bitIndex++)
                {
                    I2CPORT |= (1 << BB_SCL); // just toggle SCL, SDA stays the same
                    I2C_CLK_LOW();
                }
            }
            else // normal byte needs every bit tested
            {
                for (uint8_t bitIndex = 0; bitIndex < 8; bitIndex++)
                {
                    byteOld &= ~(1 << BB_SDA);
                    if (byteCurr & 0x80)
                    {
                        byteOld |= (1 << BB_SDA);
                    }

                    I2CPORT = byteOld;
                    I2CPORT |= (1 << BB_SCL);
                    I2C_CLK_LOW();
                    byteCurr <<= 1;
                }
            }

            // ACK bit seems to need to be set to 0, but SDA line doesn't need to be tri-state
            I2CPORT &= ~(1 << BB_SDA);
            I2CPORT |= (1 << BB_SCL); // toggle clock
            I2CPORT &= ~(1 << BB_SCL);
        }
    }

    void byte_out(uint8_t byte)
    {
        uint8_t byteOld = I2CPORT & ~((1 << BB_SDA) | (1 << BB_SCL));
        for (uint8_t bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            byteOld &= ~(1 << BB_SDA);
            if (byte & 0x80)
            {
                byteOld |= (1 << BB_SDA);
            }

            I2CPORT = byteOld;
            I2CPORT |= (1 << BB_SCL);
            I2C_CLK_LOW();
            byte <<= 1;
        }

        // ack bit
        I2CPORT = byteOld & ~(1 << BB_SDA); // set data low
        I2CPORT |= (1 << BB_SCL); // toggle clock
        I2C_CLK_LOW();
    }
}