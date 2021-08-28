#pragma once

#include "Base/containers/backfill_vector.hpp"
#include "Base/dllexports.h"
#include "Base/typedefs.h"
#include "Easing/debounce.h"
#include "Easing/linear.h"
#include <array>
#include <cstddef>

namespace easing
{

struct DLL_PUBLIC Easer
{
    backfill_vector<DebounceData, 20> debouncers;
    backfill_vector<LinearData, 20>   linears;
};


DLL_PUBLIC
void
integrate(backfill_vector<DebounceData, 20>& debouncers, int ms);


DLL_PUBLIC
void
integrate(backfill_vector<LinearData, 20>& debouncers, int ms);


DLL_PUBLIC
void
sweep(backfill_vector<DebounceData, 20>& debouncers);


inline auto
make_debounce_switch(Easer& easer, int timeout_ms) -> Debounce
{
    easer.debouncers.allocate();
    auto& item      = easer.debouncers.back();
    item.timeout_ms = timeout_ms;
    item.time_ms    = 0;
    item.state      = DebounceState::DEFAULT;
    item.ref_count  = 0;

    easing::Debounce debounce;
    debounce.set_data(&item);
    return debounce;
}


inline auto
make_linear_easer(Easer& easer, float value, float rate) -> Linear
{
    easer.linears.allocate();
    auto& data         = easer.linears.back();
    data.target_value  = value;
    data.current_value = value;
    data.rate          = rate;
    data.state         = LinearState::Default;
    data.ref_count     = 0;

    Linear item;
    item.set_data(&data);
    return item;
}

} // namespace easing
