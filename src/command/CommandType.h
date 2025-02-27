#pragma once

enum class CommandType
{
    // Device
    Reset = 'R',
    RegisterInput = 'I',
    StartFrame = 'F',
    InputValue = 'V',
    EndFrame = 'E',
    Message = 'M',
    
    // Host
    AcknowledgeReset = 'A',
    AcknowledgeFrame = 'K'
};
