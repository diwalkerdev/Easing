#pragma once
#include "typedefs.h"

namespace easing
{
enum class LinearState : uint8 {
    Default,
    Running,
};

struct LinearData {
    float       target_value;
    float       current_value;
    float       rate;
    LinearState state;
    uint8       ref_count { 0 };
};

struct Linear {
    Linear(LinearData& data)
        : data(data)
    {

        data.ref_count += 1;
    };

    ~Linear()
    {
        data.ref_count -= 1;
    }
    void init(float value, float rate)
    {
        data.target_value  = value;
        data.current_value = value;
        data.rate          = rate;
        data.state         = LinearState::Default;
    }

    void set(float value)
    {
        data.target_value = value;
        data.state        = LinearState::Running;
    }

    float get()
    {
        return data.current_value;
    }

    LinearData& data;
};


void integrate_linear(LinearData& data, float ms);

} // namespace easing