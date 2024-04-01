#include "display.h"

Display::Display()
    : _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{ }

void Display::begin()
{
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!_display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    
    _display.cp437(true);
    _display.clearDisplay();
}

void Display::flush()
{
    _display.display();
}

void Display::clear()
{
    _display.clearDisplay();
}

void Display::set_pixel(u8 x, u8 y)
{
    _display.writePixel(x, y, SSD1306_WHITE);
}

void Display::clear_pixel(u8 x, u8 y)
{
    _display.writePixel(x, y, SSD1306_BLACK);
}