#include "easing/linear.h"
using namespace easing;

void integrate_linear(LinearData& data, float ms)
{
    if (data.state == LinearState::Default)
    {
        return;
    }

    data.current_value -= data.rate;
    if (data.current_value < data.target_value)
    {
        data.state         = LinearState::Default;
        data.current_value = data.target_value;
    }
}