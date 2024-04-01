#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "audio_engine.h"
#include "display.h"
#include "paddle.h"
#include "ball.h"
#include "score.h"

AudioEngine audio_engine;
Display display;

Paddle p1(4);
Paddle p2(SCREEN_WIDTH - 4 - PADDLE_WIDTH);
Ball ball;
Score score;

GameState game_state;

void setup()
{
    display.begin();
    score.init(display);

    game_state.p1 = &p1;
    game_state.p2 = &p2;
    game_state.score = &score;

    // audio_engine.start();
}

void loop()
{
    int8_t const dir = ((millis() & 0x3FF) >> 9) * 2 - 1;

    p1.move_y(2 * dir);
    p2.move_y(5 * dir);
    ball.update(game_state, display);

    ball.draw(display);
    p1.draw(display);
    p2.draw(display);

    display.flush();
    audio_engine.tick();
}