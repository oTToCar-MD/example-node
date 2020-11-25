#pragma once

#include "main.h"
#include "uavcan/uavcan.hpp"

namespace example_node
{
class RestartRequestHandler : public uavcan::IRestartRequestHandler
{
public:
    bool handleRestartRequest(uavcan::NodeID) override
    {
        NVIC_SystemReset();

        // This line will never be hit. Therefore, the initiating node will only receive a timeout
        // response.
        return true;
    }
};
} // namespace drive_controller