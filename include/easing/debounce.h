#pragma once
#include "typedefs.h"

namespace easing
{

enum class DebounceState : uint8 {
    DEFAULT,
    RUNNING_GOT,
    RUNNING
};

struct DebounceData {
    int           timeout_ms;
    int           time_ms;
    DebounceState state;
    int8          ref_count;
};

struct Debounce {
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

void integrate_debounce(DebounceData& data, float ms);

} // namespace easing