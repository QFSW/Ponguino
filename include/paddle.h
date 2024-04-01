#include <inttypes.h>

#define PADDLE_HEIGHT 12
#define PADDLE_WIDTH 3

class Display;

class Paddle
{
public:
    Paddle(int8_t x);

    void set_y(int8_t y);
    void move_y(int8_t y_delta);

    void draw(Display& display);

    int8_t get_x() const { return _x; }
    int8_t get_y() const { return _y; }

private:
    int8_t _x;
    int8_t _y;
    int8_t _y_old;
};