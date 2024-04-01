#pragma once

#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define YELLOW_HEIGHT   16
#define YELLOW_START    0
#define BLUE_HEIGHT     48
#define BLUE_START      16

#define OLED_RESET      -1
#define SCREEN_ADDRESS  0x3C

class Display
{
public:
    Display();

    void begin();

    void flush();
    void clear();

    void set_pixel(u8 x, u8 y);
    void clear_pixel(u8 x, u8 y);

    Adafruit_SSD1306& get_inner() { return _display;  }

private:
    Adafruit_SSD1306 _display;
};
