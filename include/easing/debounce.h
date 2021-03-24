#pragma once
#include "dllexports.h"
#include "typedefs.h"

namespace easing
{

enum class DLL_PUBLIC DebounceState : uint8 {
    DEFAULT,
    RUNNING_GOT,
    RUNNING
};

struct DLL_PUBLIC DebounceData {
    int           timeout_ms;
    int           time_ms;
    DebounceState state;
    int8          ref_count;
};

struct DLL_PUBLIC Debounce {
    Debounce() = default;
    ~Debounce();

    Debounce(Debounce const& other);
    Debounce& operator=(Debounce const& other);
    // Debounce(Debounce&& other) = delete;
    // Debounce& operator=(Debounce&& other) = delete;

    void set_data(DebounceData* data_ptr)
    {
        data = data_ptr;
        data->ref_count += 1;
    };

    void reset(int timeout_ms, int time_ms)
    {
        data->timeout_ms = timeout_ms;
        data->time_ms    = time_ms;
        data->state      = DebounceState::DEFAULT;
    }

    auto get() -> bool;
    auto set(bool value) -> bool;

private:
    DebounceData* data;
};

DLL_PUBLIC void integrate_debounce(easing::DebounceData& data, float ms);

} // namespace easing
