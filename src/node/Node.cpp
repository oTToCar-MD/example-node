#include "Node.hpp"
#include "task.h"
#include "uavcan-stm32-cubehal-base/build_information.hpp"
#include "uavcan-stm32-cubehal-base/hash.hpp"
#include "uavcan-stm32-cubehal-base/unique_id.hpp"
#include "uavcan/uavcan.hpp"
#include <node/Node.hpp>
#include <uavcan-stm32-cubehal-base/node.hpp>

using base::NodeLocker;

namespace example_node
{

Node::Node()
{
}

Node::~Node()
{
}

void Node::run()
{
    auto &node = base::getNode();
    volatile int result{};

    // node specifics
    node.setNodeID(NODE_ID);
    node.setName(NODE_NAME);

    // Software / Hardware version
    uavcan::protocol::SoftwareVersion swVersion;
    swVersion.major = NODE_SW_MAJOR;
    swVersion.minor = NODE_SW_MINOR;
    swVersion.vcs_commit = build_info::CommitHashShort;
    swVersion.image_crc = bus_node_base::computeFirmwareHash();
    swVersion.optional_field_flags =
        swVersion.OPTIONAL_FIELD_FLAG_VCS_COMMIT | swVersion.OPTIONAL_FIELD_FLAG_IMAGE_CRC;
    node.setSoftwareVersion(swVersion);

    uavcan::protocol::HardwareVersion hwVersion;
    hwVersion.major = NODE_HW_MAJOR;
    hwVersion.major = NODE_HW_MINOR;
    bus_node_base::fillUniqueIdField(hwVersion, HAL_GetUIDw0(), HAL_GetUIDw1(), HAL_GetUIDw2());
    node.setHardwareVersion(hwVersion);

    // startup libuavcan
    result = node.start();
    if (result < 0)
    {
        __asm("bkpt"); //TODO handle this better
    }

    // restart request handler
    node.setRestartRequestHandler(&_restartReqHandler);

    // parameter server 
    uavcan::ParamServer paramServer{node};
    result = paramServer.start(&_paramManager);
    if (result < 0)
    {
        node.setHealthWarning();
    }

    // build info server
    uavcan::ServiceServer<GetBuildInformation> buildInfoServer{node};
    buildInfoServer.start(
        [](const uavcan::ReceivedDataStructure<GetBuildInformation::Request> &request,
           GetBuildInformation::Response &response) {
            response.branch_name = build_info::BranchName;
            response.build_time = build_info::BuildTime;
            response.commit_hash = build_info::CommitHashLong;
            response.is_debug = build_info::IsDebugBuild;
            response.is_dirty = build_info::IsDirty;
        });

    node.setModeOperational();

    // spin
    TickType_t xLastWakeTime = xTaskGetTickCount();
    uint32_t tLastPosAndTorque = 0;
    while (true)
    {
        // volatile uint32_t stack = uxTaskGetStackHighWaterMark(NULL);
        {
            NodeLocker locker;
            base::getNode().spinOnce();
        }

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(2));
    }
}

Node &Node::instance()
{
    static Node *inst = new Node();
    return *inst;
}

} // namespace example_node

extern "C" void startNodeTask(void *argument)
{
    example_node::Node::instance().run();
    for (;;)
    {
        // should never get here, but good practice nontheless
        vTaskSuspend(nullptr);
    }
}
