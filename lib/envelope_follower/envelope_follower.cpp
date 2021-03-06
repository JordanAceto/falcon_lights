#include "envelope_follower.hpp"

Envelope_Follower::Envelope_Follower()
{
    lpf.setFrequencyRange(1.0, 50.0);
    lpf.input.plugIn(&fwr.output);
    lpf.cutoff_input.plugIn(&decay_control.output);
}

void Envelope_Follower::setSampleRate(float sample_rate)
{
    Is_Tickable::setSampleRate(sample_rate);
    lpf.setSampleRate(sample_rate);
}

void Envelope_Follower::tick()
{
    if (fwr.output.get() > peak)
        peak = fwr.output.get();
    else
        peak = peak > 0.0 ? peak - 0.005 : 0.0;

    fwr.output.set(peak);

    lpf.tick();
}

void Envelope_Follower::process()
{
    fwr.process();
    decay_control.process();
    lpf.process();

    output.set(lpf.output.get());
}
