#include "Arduino_Waldo.h"


Waldo::Waldo()
{
}

Waldo::~Waldo()
{    
}

void Waldo::setup() 
{
    Device.Setup();
}
  
void Waldo::add_input_analog(const char* label, int pin) 
{
    FInput input = FInput{
        .label = label,
        .pin = pin,
        .id = Device.AssignInputId(),
        .type = EInputType::Analog
    };

    Device.AddInput(input);
}

void Waldo::add_input_digital(const char* label, int pin) 
{
    FInput input = FInput{
        .label = label,
        .pin = pin,
        .id = Device.AssignInputId(),
        .type = EInputType::Digital
    };

    Device.AddInput(input);
}
  
void Waldo::loop() 
{
    Device.Loop();
}