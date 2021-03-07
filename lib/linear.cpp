#include "easing/linear.h"

DLL_PUBLIC void test_function()
{
}

void easing::integrate_linear(LinearData& data, float ms)
{
    if (data.state == LinearState::Default)
    {
        return;
    }

    data.current_value -= (data.rate * (ms / 1000));
    if (data.current_value <= data.target_value)
    {
        data.state         = LinearState::Default;
        data.current_value = data.target_value;
    }
}
