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

    int16_t _x;
    int16_t _y;
    uint8_t _x_old;
    uint8_t _y_old;
    int8_t _speed_x;
    int8_t _speed_y;
};