#pragma once

enum class State
{
    None = 0,
    Reset,
    WaitAcknowledgeReset,
    SendFrame,
    WaitAcknowledgeFrame
};
