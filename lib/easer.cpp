#include "easing/debounce.h"
#include "easing/easing.h"
#include "easing/linear.h"


void easing::integrate(backfill_vector<easing::DebounceData, 20>& debouncers, int ms)
{
    for (auto& item : debouncers)
    {
        easing::integrate_debounce(item, ms);
    }
}

void easing::integrate(backfill_vector<easing::LinearData, 20>& linear_easers, int ms)
{
    for (auto& item : linear_easers)
    {
        easing::integrate_linear(item, ms);
    }
}

void easing::sweep(backfill_vector<easing::DebounceData, 20>& debouncers)
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