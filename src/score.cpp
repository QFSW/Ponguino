#include "score.h"

#include "display.h"
#include "utils.h"

#define CHAR_MAG 1
#define CHAR_WIDTH (8 * CHAR_MAG)
#define CHAR_HEIGHT (8 * CHAR_MAG)

#define P1_SCORE_END (SCREEN_WIDTH / 2 - CHAR_WIDTH - CHAR_WIDTH / 2)
#define P2_SCORE_START (P1_SCORE_END + 3 * CHAR_WIDTH)

#define INITIAL_START (P1_SCORE_END - CHAR_WIDTH)

void Score::init(Display& display)
{
    // inner.setTextSize(CHAR_MAG);
    // inner.setTextColor(SSD1306_WHITE);

    display.print(INITIAL_START, 0, "0 - 0");
}

void Score::get_digits_rv(uint16_t score_in, uint8_t digits_rv_out[MAX_DIGITS], uint8_t& num_out)
{
    uint32_t remainder = score_in;
    uint8_t digit = 0;
    num_out = 0;

    do
    {
        utils::divmod10(remainder, remainder, digit);
        digits_rv_out[num_out] = digit;
        num_out++;
    } while (remainder > 0);
}

void Score::write_digits(Display& display, uint8_t start, uint8_t digits_rv[MAX_DIGITS], uint8_t num_digits)
{
    // display.fill_rect(start, 0, CHAR_WIDTH * num_digits, CHAR_HEIGHT, false);

    // Loop over stack backwards to print digits
    uint8_t cursor_x = start;
    for (int8_t i = num_digits - 1; i >= 0; i--)
    {
        display.print_char(cursor_x, 0, '0' + digits_rv[i]);
        cursor_x += CHAR_WIDTH;
    }
}

void Score::inc_p1(Display& display)
{
    if (++_p1_score > MAX_SCORE)
    {
        _p1_score = 0;
    }

    uint8_t digits_rv[MAX_DIGITS];
    uint8_t num_digits;
    get_digits_rv(_p1_score, digits_rv, num_digits);
    write_digits(display, P1_SCORE_END - num_digits * CHAR_WIDTH, digits_rv, num_digits);
}

void Score::inc_p2(Display& display)
{
    if (++_p2_score > MAX_SCORE)
    {
        _p2_score = 0;
    }

    uint8_t digits_rv[MAX_DIGITS];
    uint8_t num_digits;
    get_digits_rv(_p2_score, digits_rv, num_digits);
    write_digits(display, P2_SCORE_START, digits_rv, num_digits);
}