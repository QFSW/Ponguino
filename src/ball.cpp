#include "ball.h"

#include "display.h"
#include "paddle.h"
#include "score.h"

#define BALL_END_X SCREEN_WIDTH - BALL_WIDTH
#define BALL_END_Y BLUE_HEIGHT - BALL_WIDTH

#define INITIAL_X SCREEN_WIDTH / 2 - BALL_WIDTH / 2
#define INITIAL_y BLUE_HEIGHT / 2 - BALL_WIDTH / 2

Ball::Ball()
{
    init();

    _x_old = _x;
    _y_old = _y;
}

void Ball::update(GameState& game_state, Display& display)
{
    u8 const p1_x = game_state.p1->get_x();
    u8 const p1_y = game_state.p1->get_y();
    u8 const p2_x = game_state.p2->get_x();
    u8 const p2_y = game_state.p2->get_y();

    _x += _speed_x;
    _y += _speed_y;

    // Left wall
    if (_x < 0)
    {
        init();
        game_state.score->inc_p2(display);
    }
    // Left paddle
    else if (
        _x <= (p1_x + PADDLE_WIDTH) &&
        _y >= (p1_y) &&
        _y <= (p1_y + PADDLE_HEIGHT)
    )
    {
        _x = p1_x + PADDLE_WIDTH;
        _speed_x = abs(_speed_x);
        
        const int8_t delta_y = _y - p1_y - PADDLE_HEIGHT / 2;
        _speed_y = delta_y * BALL_SPEED_Y_MAX / (PADDLE_HEIGHT / 2);
    }

    // Right wall
    if (_x > BALL_END_X)
    {
        init();
        game_state.score->inc_p1(display);
    }
    // Right paddle
    else if (
        _x >= (p2_x) &&
        _y >= (p2_y) &&
        _y <= (p2_y + PADDLE_HEIGHT)
    )
    {
        _x = p2_x - 1;
        _speed_x = -1 * abs(_speed_x);

        const int8_t delta_y = _y - p2_y - PADDLE_HEIGHT / 2;
        _speed_y = delta_y * BALL_SPEED_Y_MAX / (PADDLE_HEIGHT / 2);
    }

    // Top wall
    if (_y < 0)
    {
        _y = 0;
        _speed_y *= - 1;
    }

    // Bottom wall
    if (_y > BALL_END_Y)
    {
        _y = BALL_END_Y;
        _speed_y *= - 1;
    }
}

void Ball::draw(Display& display)
{
    display.get_inner().fillRect(_x_old, BLUE_START + _y_old, BALL_WIDTH, BALL_WIDTH, SSD1306_BLACK);
    display.get_inner().fillRect(_x, BLUE_START + _y, BALL_WIDTH, BALL_WIDTH, SSD1306_WHITE);

    _x_old = _x;
    _y_old = _y;
}

void Ball::init()
{
    _x = INITIAL_X;
    _y = INITIAL_y;

    _speed_x = BALL_SPEED_X * (random(0, 2) * 2 - 1);
    _speed_y = random(-BALL_SPEED_X, BALL_SPEED_X + 1);
}