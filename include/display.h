#pragma once

#include <Arduino.h>

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define YELLOW_HEIGHT   16
#define YELLOW_START    0
#define BLUE_HEIGHT     48
#define BLUE_START      16

#define OLED_RESET      -1
#define OLED_ADDR       0x3C

#define BACK_BUFFER_SIZE ((SCREEN_WIDTH * SCREEN_HEIGHT / 8) + 1)

class Display
{
public:
    Display(uint8_t* back_buffer);

    void begin();

    void flush();
    void clear();

    void print(uint8_t x, uint8_t y, const char* str);
    void print_char(uint8_t x, uint8_t y, char c);
    void write_pixel(uint8_t x, uint8_t y, bool high);
    void fill_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool high);

private:
    void i2c_write(const uint8_t* data, int len);

    uint8_t* _full_buffer;
    uint8_t* _data_buffer;
};
