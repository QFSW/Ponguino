#include <inttypes.h>

#include "game_state.h"

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

    float _x;
    float _y;
    float _speed_x;
    float _speed_y;

    uint8_t _x_old;
    uint8_t _y_old;
};