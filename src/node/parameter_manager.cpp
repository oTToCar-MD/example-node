#include "parameter_manager.hpp"
#include "parameter_names.hpp"

using namespace uavcan::protocol::param;

namespace
{
float testParam;
}

namespace example_node
{
void ParameterManager::getParamNameByIndex(Index index, Name &outName) const
{
    switch (index)
    {
        case 0:
            outName = param::TestParam;
            break;
    }
}

void ParameterManager::assignParamValue(const Name &name, const Value &value)
{
    if (name == param::TestParam)
    {
        if (value.is(Value::Tag::real_value))
        {
            testParam = *value.as<Value::Tag::real_value>();
        }
    }
}

void ParameterManager::readParamValue(const Name &name, Value &outValue) const
{
    if (name == param::TestParam)
    {
        outValue.to<Value::Tag::real_value>() = testParam;
    }
}

void ParameterManager::readParamDefaultMaxMin(const Name &name, Value &outDef, NumericValue &outMax,
                                              NumericValue &outMin) const
{
    if (name == param::TestParam)
    {
        outDef.to<Value::Tag::real_value>() = 1;
        outMax.to<NumericValue::Tag::real_value>() = 2;
        outMin.to<NumericValue::Tag::real_value>() = 0;
    }
}

int ParameterManager::saveAllParams()
{
    return 0;
}

int ParameterManager::eraseAllParams()
{
    return 0;
}
} // namespace example_node