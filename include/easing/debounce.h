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
    Debounce(DebounceData& item);
    ~Debounce();
    Debounce(Debounce const& other);
    auto operator=(Debounce const& other) -> Debounce&;

    // Move - deleted as same as copy construction.
    Debounce(Debounce&& other) = delete;
    auto operator=(Debounce&& other) -> Debounce& = delete;

    // Accessors
    auto get() -> bool;

    // Modifiers
    auto set(bool value) -> bool;


private:
    DebounceData& data;
};

DLL_PUBLIC void integrate_debounce(easing::DebounceData& data, float ms);

} // namespace easing
