#include "score.h"

#include "display.h"

void Score::init(Display& display)
{
    auto& inner = display.get_inner();

    inner.setTextSize(CHAR_MAG);
    inner.setTextColor(SSD1306_WHITE);
    inner.setCursor(P1_SCORE_START, 0);

    inner.write("0 - 0");
}

void Score::set_score(u8 score, u8 start, Display& display)
{
    auto& inner = display.get_inner();

    inner.fillRect(start, 0, CHAR_WIDTH, CHAR_HEIGHT, SSD1306_BLACK);
    inner.setCursor(start, 0);
    inner.write('0' + score);
}

void Score::inc_p1(Display& display)
{
    set_score(++_p1_score, P1_SCORE_START, display);
}

void Score::inc_p2(Display& display)
{
    set_score(++_p2_score, P2_SCORE_START, display);
}