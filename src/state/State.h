#pragma once

enum class State
{
    None,
    Reset,
    WaitAcknowledgeReset,
    SendFrame,
    WaitAcknowledgeFrame
};
