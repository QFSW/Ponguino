#include "display.h"

#include "utils.h"
#include "display_cmds.h"
#include "display_font.h"
#include "fast_i2c.h"

#define WRITE_CMD_LIST(...) \
    uint8_t UNIQUE_VAR(cmd_list)[] = {CMD_START, __VA_ARGS__}; \
    i2c_write(UNIQUE_VAR(cmd_list), sizeof(UNIQUE_VAR(cmd_list)));

Display::Display(uint8_t* back_buffer)
    : _full_buffer(back_buffer)
    , _data_buffer(back_buffer + 1)
{
    // First byte of backbuffer should always be the data command
    _full_buffer[0] = CMD_SETSTARTLINE;

    clear();
}

void Display::begin()
{
    I2CDDR &= ~(1 << BB_SDA);
    I2CDDR &= ~(1 << BB_SCL); // let them float high
    I2CPORT |= (1 << BB_SDA); // set both lines to get pulled up
    I2CPORT |= (1 << BB_SCL);

    WRITE_CMD_LIST(
        CMD_DISPLAYOFF,
        CMD_SETMULTIPLEX,
        0x3F,
        CMD_SETDISPLAYOFFSET,
        CMD_START,
        CMD_SETSTARTLINE, 0xA1,
        CMD_COMSCANDEC,
        CMD_SETCOMPINS, 0x12,
        CMD_SETCONTRAST, 0xFF,
        CMD_DISPLAYALLON_RESUME,
        CMD_NORMALDISPLAY,
        CMD_SETDISPLAYCLOCKDIV, 0x80,
        CMD_CHARGEPUMP, 0x14,
        CMD_DISPLAYON,
        CMD_MEMORYMODE,
        0x00 // Horizontal
    );

    flush();
}

void Display::flush()
{
    WRITE_CMD_LIST(
        CMD_PAGEADDR,
        0,                      // Page start address
        0xFF,                   // Page end (not really, but works here)
        CMD_COLUMNADDR, 0
    );

    WRITE_CMD_LIST(SCREEN_WIDTH - 1); // Column end address

    i2c_write(_full_buffer, BACK_BUFFER_SIZE);
}

void Display::clear()
{
    memset(_data_buffer, 0, BACK_BUFFER_SIZE - 1);
}

void Display::print(uint8_t x, uint8_t y, const char* str)
{
    while (*str != 0)
    {
        print_char(x, y, *str++);
        x += 8;
    }
}

void Display::print_char(uint8_t x, uint8_t y, char c)
{
    uint16_t const font_offset = c * 8;
    uint16_t const data_offset = (y >> 3) * SCREEN_WIDTH + x;
    memcpy_P(_data_buffer + data_offset, font8x8 + font_offset, 8);
}

void Display::write_pixel(uint8_t x, uint8_t y, bool high)
{
    // Each byte corresponds to an 8px tall column
    uint16_t const byteIndex = (y >> 3) * SCREEN_WIDTH + x;
    uint16_t const bitIndex = y & 0b111;

    if (high)
    {
        _data_buffer[byteIndex] |= (1 << bitIndex);
    }
    else
    {
        _data_buffer[byteIndex] &= ~(1 << bitIndex);
    }
}

void Display::fill_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool high)
{
    // TODO: optimize
    for (uint8_t i = 0; i < width; ++i)
    {
        for (uint8_t j = 0; j < height; ++j)
        {
            write_pixel(x + i, y + j, high);
        }
    }
}

void Display::i2c_write(const uint8_t* data, int len)
{
    fast_i2c::begin(OLED_ADDR);
    fast_i2c::write(data, len);
    fast_i2c::end();
}