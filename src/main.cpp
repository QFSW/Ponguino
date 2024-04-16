#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "audio_engine.h"
#include "display.h"
#include "paddle.h"
#include "ball.h"
#include "score.h"

#define USE_TIMER_1 true
#include "TimerInterrupt.h"

AudioEngine audio_engine;
Display display;

Paddle p1(4);
Paddle p2(SCREEN_WIDTH - 4 - PADDLE_WIDTH);
Ball ball;
Score score;

GameState game_state;

void audio_thread()
{
    audio_engine.tick();
}

void setup()
{
    display.begin();
    score.init(display);

    p1.init(A0, 0 , 652);
    p2.init(A1, 29, 652);

    game_state.p1 = &p1;
    game_state.p2 = &p2;
    game_state.score = &score;

    audio_engine.start();

    ITimer1.init();
    ITimer1.attachInterrupt(1000, audio_thread);
}

void loop()
{
    p1.tick();
    p2.tick();
    ball.update(game_state, display);

    ball.draw(display);
    p1.draw(display);
    p2.draw(display);

    display.flush();
}