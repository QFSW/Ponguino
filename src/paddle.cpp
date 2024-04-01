#include "paddle.h"

#include "display.h"

Paddle::Paddle(int8_t x)
    : _x(x)
    , _y(BLUE_HEIGHT / 2)
{ }

void Paddle::move_y(int8_t y_delta)
{
    _y += y_delta;
    _y = min(_y, BLUE_HEIGHT - PADDLE_HEIGHT);
    _y = max(_y, 0);
}

void Paddle::draw(Display& display)
{
    display.get_inner().fillRect(_x, BLUE_START + _y_old, PADDLE_WIDTH, PADDLE_HEIGHT, SSD1306_BLACK);
    display.get_inner().fillRect(_x, BLUE_START + _y, PADDLE_WIDTH, PADDLE_HEIGHT, SSD1306_WHITE);

    _y_old = _y;
}