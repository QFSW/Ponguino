#include <inttypes.h>

#include "game_state.h"

#define BALL_WIDTH 2
#define BALL_SPEED_X 3
#define BALL_SPEED_Y_MAX 6

class Display;
class Score;

class Ball
{
public:
    Ball();

    void update(GameState& game_state, Display& display);
    void draw(Display& display);

private:
    void init();

    int16_t _x;
    int16_t _y;
    uint8_t _x_old;
    uint8_t _y_old;
    int8_t _speed_x;
    int8_t _speed_y;
};