#pragma once

#include "containers/backfill_vector.hpp"
#include "dllexports.h"
#include "easing/debounce.h"
#include "easing/linear.h"
#include "typedefs.h"
#include <array>
#include <cstddef>

namespace easing
{

struct DLL_PUBLIC Easer {
    backfill_vector<DebounceData, 20> debouncers;
    backfill_vector<LinearData, 20>   linears;
};

DLL_PUBLIC
void integrate(backfill_vector<DebounceData, 20>& debouncers, int ms);

DLL_PUBLIC
void sweep(backfill_vector<DebounceData, 20>& debouncers);

inline auto make_debounce_switch(Easer& easer, int timeout_ms) -> Debounce
{
    easer.debouncers.allocate();
    auto& item      = easer.debouncers.back();
    item.timeout_ms = timeout_ms;
    item.time_ms    = 0;
    item.state      = DebounceState::DEFAULT;
    item.ref_count  = 0;

    return { item };
}

inline auto make_linear_easer(Easer& easer, float value, float rate) -> Linear
{
    easer.linears.allocate();
    auto& item         = easer.linears.back();
    item.target_value  = value;
    item.current_value = value;
    item.rate          = rate;
    item.state         = LinearState::Default;
    item.ref_count     = 0;
    return { item };
}

} // namespace easing
