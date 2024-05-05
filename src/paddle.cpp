#include "paddle.h"

#include "display.h"

Paddle::Paddle(int8_t x)
    : _stabilize_frames(0)
    , _x(x)
    , _y(BLUE_HEIGHT / 2)
{ }

void Paddle::init(uint8_t pot_pin, uint16_t pot_min, uint16_t pot_max)
{
    _pot_pin = pot_pin;
    _pot_min = pot_min;
    _pot_mul = 1.0f / (pot_max - pot_min);

    pinMode(_pot_pin, INPUT);
}

void Paddle::tick()
{
    float const rawIn = analogRead(_pot_pin);
    float const inNorm = (rawIn - _pot_min) * _pot_mul;
    int8_t const mappedIn = static_cast<int8_t>(inNorm * (BLUE_HEIGHT - PADDLE_HEIGHT));

    set_y(mappedIn);
}

void Paddle::set_y(int8_t y)
{
    int8_t new_y = min(y, BLUE_HEIGHT - PADDLE_HEIGHT);
    new_y = max(new_y, 0);

    // If the new value is sufficiently different, apply immediately
    // otherwise wait until we've been at the new value for some amount of time
    // this helps to filter out wobble from electrical noise
    if (abs(new_y - _y) > STABILIZE_WINDOW)
    {
        _y = new_y;
        _stabilize_frames = 0;
    }
    else if (new_y == _y)
    {
        _stabilize_frames = 0;
    }
    else
    {
        if (++_stabilize_frames >= STABILIZE_LENGTH)
        {
            _y = new_y;
            _stabilize_frames = 0;
        }
    }
}

void Paddle::move_y(int8_t y_delta)
{
    set_y(_y + y_delta);
}

void Paddle::draw(Display& display)
{
    display.get_inner().fillRect(_x, BLUE_START + _y_old, PADDLE_WIDTH, PADDLE_HEIGHT, SSD1306_BLACK);
    display.get_inner().fillRect(_x, BLUE_START + _y, PADDLE_WIDTH, PADDLE_HEIGHT, SSD1306_WHITE);

    _y_old = _y;
}