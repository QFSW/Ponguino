#include "ball.h"

#include "display.h"
#include "paddle.h"
#include "score.h"

#define BALL_WIDTH 2
#define BALL_SPEED_X 1.5f
#define BALL_SPEED_Y_MAX 1.5f
#define BALL_SPEED_INIT 0.75f

#define BALL_END_X (SCREEN_WIDTH - BALL_WIDTH)
#define BALL_END_Y (BLUE_HEIGHT - BALL_WIDTH)

#define INITIAL_X (SCREEN_WIDTH / 2 - BALL_WIDTH / 2)
#define INITIAL_y (BLUE_HEIGHT / 2 - BALL_WIDTH / 2)

Ball::Ball()
{
    init();

    _x_old = static_cast<uint8_t>(_x);
    _y_old = static_cast<uint8_t>(_y);
}

void Ball::update(GameState& game_state, Display& display)
{
    uint8_t const p1_x = game_state.p1->get_x();
    uint8_t const p1_y = game_state.p1->get_y();
    uint8_t const p2_x = game_state.p2->get_x();
    uint8_t const p2_y = game_state.p2->get_y();

    _x += _speed_x;
    _y += _speed_y;

    int8_t const x_quant = static_cast<uint8_t>(_x);
    int8_t const y_quant = static_cast<uint8_t>(_y);

    // Left wall
    if (x_quant < 0)
    {
        init();
        game_state.score->inc_p2(display);
    }
    // Left paddle
    else if (
        x_quant <= (p1_x + PADDLE_WIDTH) &&
        y_quant >= (p1_y) &&
        y_quant <= (p1_y + PADDLE_HEIGHT)
    )
    {
        _x = p1_x + PADDLE_WIDTH;
        _speed_x = BALL_SPEED_X;
        
        const float delta_y = (y_quant - p1_y) - PADDLE_HEIGHT / 2;
        _speed_y = delta_y * BALL_SPEED_Y_MAX / (PADDLE_HEIGHT / 2);
    }

    // Right wall
    if (x_quant > BALL_END_X)
    {
        init();
        game_state.score->inc_p1(display);
    }
    // Right paddle
    else if (
        x_quant >= (p2_x) &&
        y_quant >= (p2_y) &&
        y_quant <= (p2_y + PADDLE_HEIGHT)
    )
    {
        _x = p2_x - 1;
        _speed_x = -BALL_SPEED_X;

        const float delta_y = (y_quant - p2_y) - PADDLE_HEIGHT / 2;
        _speed_y = delta_y * BALL_SPEED_Y_MAX / (PADDLE_HEIGHT / 2);
    }

    // Top wall
    if (y_quant < 0)
    {
        _y = 0;
        _speed_y *= - 1;
    }

    // Bottom wall
    if (y_quant > BALL_END_Y)
    {
        _y = BALL_END_Y;
        _speed_y *= - 1;
    }
}

void Ball::draw(Display& display)
{
    uint8_t const x_quant = static_cast<uint8_t>(_x);
    uint8_t const y_quant = static_cast<uint8_t>(_y);

    display.fill_rect(_x_old, BLUE_START + _y_old, BALL_WIDTH, BALL_WIDTH, false);
    display.fill_rect(x_quant, BLUE_START + y_quant, BALL_WIDTH, BALL_WIDTH, true);
    
    _x_old = x_quant;
    _y_old = y_quant;
}

void Ball::init()
{
    _x = INITIAL_X;
    _y = INITIAL_y;

    _speed_x = BALL_SPEED_INIT * (random(0, 2) * 2 - 1);
    _speed_y = random(-128, 129) / 128.0f * BALL_SPEED_INIT;
}