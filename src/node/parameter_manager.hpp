#pragma once

#include "uavcan/protocol/param_server.hpp"

namespace example_node
{
class ParameterManager : public uavcan::IParamManager
{
public:
    void getParamNameByIndex(Index index, Name &outName) const override;
    void assignParamValue(const Name &name, const Value &value) override;
    void readParamValue(const Name &name, Value &outValue) const override;
    void readParamDefaultMaxMin(const Name &name, Value &outDef, NumericValue &outMax,
                                NumericValue &outMin) const override;

    int saveAllParams() override;
    int eraseAllParams() override;
};
} // namespace drive_controller