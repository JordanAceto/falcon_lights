#include "lfo.hpp"

LFO::LFO()
{
    waveshape[SINE]     = new Sine_Shaper;
    waveshape[TRIANGLE] = new Naive_Triangle_Shaper;
    waveshape[UP_SAW]   = new Naive_Up_Saw_Shaper;
    waveshape[DOWN_SAW] = new Naive_Down_Saw_Shaper;
    waveshape[SQUARE]   = new Naive_Square_Shaper;
    waveshape[RANDOM]   = new Random_Shaper;
}

LFO::~LFO()
{
    for (auto shape : waveshape)
        delete shape;
}

void LFO::setSampleRate(float sample_rate)
{
    core.setSampleRate(sample_rate);
}

void LFO::tick()
{
    core.tick();
}

void LFO::process()
{
    frequency_input.process();
    core.setFrequency(mapInput(frequency_input.get(), F1, F2));

    if (sync_input.isPluggedIn())
    {
        sync_input.process();
        if (sync_input.risingEdge())
        core.reset();
    }

    for (int shape = 0; shape < NUM_LFO_SHAPES; shape ++)
        output[shape].set(waveshape[shape]->process(core));
}
