#include <inttypes.h>

#define PADDLE_HEIGHT 13
#define PADDLE_WIDTH 3

#define STABILIZE_WINDOW 1
#define STABILIZE_LENGTH 3

class Display;

class Paddle
{
public:
    Paddle(int8_t x);

    void init(uint8_t pot_pin, uint16_t pot_min, uint16_t pot_max);

    void tick();
    void draw(Display& display);

    int8_t get_x() const { return _x; }
    int8_t get_y() const { return _y; }

private:
    void set_y(int8_t y);
    void move_y(int8_t y_delta);

    float _pot_mul;
    uint16_t _pot_min;
    uint8_t _pot_pin;
    uint8_t _stabilize_frames;

    int8_t _x;
    int8_t _y;
    int8_t _y_old;
};