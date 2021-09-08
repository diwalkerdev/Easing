#pragma once
#include "Base/dllexports.h"
#include "Base/typedefs.h"

namespace easing
{

enum class LinearState : uint8
{
    Default,
    Running,
};

struct DLL_PUBLIC LinearData
{
    float       target_value;
    float       current_value;
    float       rate;
    LinearState state;
    uint8       ref_count;
};

struct DLL_PUBLIC Linear
{
    Linear() = default;
    ~Linear()
    {
        if (data)
        {
            data->ref_count -= 1;
        }
    }

    Linear(Linear const& other)
    {
        data = other.data;
        data->ref_count += 1;
    }

    Linear&
    operator=(Linear const& other)
    {
        data = other.data;
        data->ref_count += 1;
        return *this;
    }

    // Linear(Linear&& other) = delete;
    // Linear& operator=(Linear&& other) = delete;

    void
    set_data(LinearData* data_ptr)
    {
        data = data_ptr;
        data->ref_count += 1;
    };

    void
    reset(float value, float rate)
    {
        data->target_value  = value;
        data->current_value = value;
        data->rate          = rate;
        data->state         = LinearState::Default;
    }

    void
    set(float value)
    {
        data->target_value = value;
        data->state        = LinearState::Running;
    }

    float
    get()
    {
        return data->current_value;
    }

private:
    // Note: data must be a pointer as Linear must be default constructable so it can be put in an array.
    LinearData* data { nullptr };
};


DLL_PUBLIC void
integrate_linear(LinearData& data, float ms);

} // namespace easing