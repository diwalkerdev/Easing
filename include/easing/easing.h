#pragma once

#include "containers/backfill_vector.hpp"
#include "easing/debounce.h"
#include "typedefs.h"
#include <array>
#include <cstddef>

namespace easing
{

struct Easer {
    backfill_vector<DebounceData, 20> debouncers;
};

inline void integrate(backfill_vector<DebounceData, 20>& debouncers, int ms)
{
    for (auto& item : debouncers)
    {
        integrate_debounce(item, ms);
    }
}

inline void sweep(backfill_vector<DebounceData, 20>& debouncers)
{
    for (size_t i = 0; i < debouncers.size(); ++i)
    {
        auto& item = debouncers[i];
        if (item.ref_count == 0)
        {
            debouncers.remove(i);
        }
    }
}

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

} // namespace easing
