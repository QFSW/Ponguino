#include <inttypes.h>

class Display;

#define MAX_DIGITS 3
#define MAX_SCORE 999

class Score
{
public:
    void init(Display& display);

    void inc_p1(Display& display);
    void inc_p2(Display& display);

private:
    // Decomposes number into reverse stack of digits
    // i.e 15 --> [5, 1, 0]
    void get_digits_rv(uint16_t score_in, uint8_t digits_rv_out[MAX_DIGITS], uint8_t& num_out);
    void write_digits(Display& display, uint8_t start, uint8_t digits_rv[MAX_DIGITS], uint8_t num_digits);

    uint16_t _p1_score;
    uint16_t _p2_score;
};