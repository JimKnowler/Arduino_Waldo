#pragma once

namespace command
{
    enum class ECommandType : char
    {
        // Device
        RegisterInput = 'I',
        StartFrame = 'F',
        InputValue = 'V',
        EndFrame = 'E',
        Message = 'M',
        
        // Host
        AcknowledgeReset = 'A',
        AcknowledgeFrame = 'K',

        // Device + Host
        Reset = 'R',
    };
}
