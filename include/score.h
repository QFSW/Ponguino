#include <inttypes.h>

#define CHAR_MAG 2
#define CHAR_WIDTH 6 * CHAR_MAG
#define CHAR_HEIGHT 8 * CHAR_MAG

#define P1_SCORE_START (SCREEN_WIDTH / 2 - (int)(CHAR_WIDTH * 2.5))
#define P2_SCORE_START P1_SCORE_START + 4 * CHAR_WIDTH

class Display;

class Score
{
public:
    void init(Display& display);

    void inc_p1(Display& display);
    void inc_p2(Display& display);

private:
    void set_score(uint8_t score, uint8_t start, Display& display);

    uint8_t _p1_score;
    uint8_t _p2_score;
    char _score_buf[6];
};