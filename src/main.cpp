#include <Arduino.h>
#include <synth_library.hpp>
#include "Mode.hpp"
#include "Circular_Linked_List.hpp"

const int PUSH_BUTTON_PIN = 7;

Arduino_Digital_Input push_button(PUSH_BUTTON_PIN);
Gate_Input button_reader;

Circular_Linked_List<Mode&> mode_list;

Basic_Slider_Mode basic_slider_mode;
Crazy_Disco_Mode crazy_disco_mode;

void setup()
{
    mode_list.add(basic_slider_mode);
    mode_list.add(crazy_disco_mode);

    button_reader.plugIn(&push_button.output);

    Mode::init();
}

void loop()
{
    push_button.process();
    button_reader.process();

    if (button_reader.risingEdge())
    {
        mode_list.moveTravellerOneForward();
    }

    mode_list.getTraveller().execute();
}
