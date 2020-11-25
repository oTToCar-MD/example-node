#pragma once
#include "FreeRTOS.h"
#include <node/parameter_manager.hpp>
#include <node/restart_request_handler.hpp>

namespace example_node
{

class Node
{
private:
    static constexpr auto NODE_NAME = "com.github.ottocarmd.examplenode";
    static constexpr auto NODE_ID = 42;

    static constexpr auto NODE_SW_MAJOR = 1;
    static constexpr auto NODE_SW_MINOR = 0;
    static constexpr auto NODE_HW_MAJOR = 1;
    static constexpr auto NODE_HW_MINOR = 0;

    RestartRequestHandler _restartReqHandler;
    ParameterManager _paramManager;

public:
    Node();
    ~Node();

    void run();
    static Node& instance();
};
} // namespace example_node
