#include "easing/debounce.h"
#include "easing/easing.h"


DLL_PUBLIC
void easing::integrate(backfill_vector<easing::DebounceData, 20>& debouncers, int ms)
{
    for (auto& item : debouncers)
    {
        integrate_debounce(item, ms);
    }
}

DLL_PUBLIC
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