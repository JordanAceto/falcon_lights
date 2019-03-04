#pragma once

#include "FastLED.h"
#include <synth_library.hpp>

class Mode
{
public:
    static void init();

    void execute();

protected:
    static const int NUM_LEDS = 23;
    static const int LED_DATA_PIN = 2;
    static const int SLIDER_PIN = 5;

    static CRGB leds[NUM_LEDS];
    static bool leds_created;

    static Arduino_Analog_Input slider;

    int hue = 135;
    int saturation = 255;
    int brightness = 200;

    virtual void setLEDs() = 0;

    // the sample rate has something wrong with it, find out what
    static const uint32_t sample_period_in_micros = 1000000.0 / g_sample_rate;
    static uint32_t last_tick;

    virtual void onTick() = 0;

};

class Basic_Slider_Mode : public Mode
{
public:
    void onTick() override;
    void setLEDs() override;
};

class Crazy_Disco_Mode : public Mode
{
public:
    Crazy_Disco_Mode();

    void onTick() override;
    void setLEDs() override;

private:
    LFO lfo;

};
