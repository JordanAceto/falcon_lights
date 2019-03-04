#include "Mode.hpp"

CRGB Mode::leds[NUM_LEDS];

Arduino_Analog_Input Mode::slider(SLIDER_PIN);

bool Mode::leds_created = false;

uint32_t Mode::last_tick = 0;

void Mode::init()
{
    pinMode(LED_DATA_PIN, OUTPUT);
    if (!leds_created)
        FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);
    leds_created = true;
}

void Mode::execute()
{
    if (micros() - last_tick >= sample_period_in_micros)
    {
        last_tick = micros();
        onTick();
    }

    setLEDs();
    FastLED.show();
}

void Basic_Slider_Mode::onTick()
{
    slider.process();
}

void Basic_Slider_Mode::setLEDs()
{
    brightness = slider.output.get() * 256;

    for (auto &led : leds)
    {
        led = CHSV(hue, saturation, brightness);
    }
}

Crazy_Disco_Mode::Crazy_Disco_Mode()
{
    lfo.setSampleRate(g_sample_rate);
    lfo.setFrequencyRange(40, 500); // something is wrong with the frequency setup
    lfo.frequency_input.plugIn(&slider.output);
}

void Crazy_Disco_Mode::onTick()
{
    slider.process();
    lfo.tick();
    lfo.process();
}

void Crazy_Disco_Mode::setLEDs()
{
    hue = (lfo.output[LFO::RANDOM].get() + 1) * 128;

    for (auto &led : leds)
    {
        led = CHSV(hue, saturation, brightness);
    }
}
