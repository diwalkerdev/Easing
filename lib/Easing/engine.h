#pragma once

#include "Base/containers/backfill_vector.hpp"
#include "Base/dllexports.h"
#include "Easing/Easers/linear.h"
#include "Easing/Easers/polynomial.h"
#include "Easing/base.h"
#include "Easing/float.h"


public_struct Easing_Engine
{
    backfill_vector<Easing_Linear, 10>               linear;
    backfill_vector<Easing_PolynomialProperties, 10> poly;
};

extern Easing_Engine global_bfv;


public_func void
Easing_Init(Easing_Engine& engine, Easing_Type type, Easing_Properties** values);


public_func void
Easing_Free(Easing_Engine& engine);


template <typename Tp, size_t Size>
void
Easing_EngineRemove(backfill_vector<Tp, Size>& container, int index)
{
    container.remove(index);
    auto& item = container[index];

    if ((container.size() > 0) && (item.base_props.back_reference != nullptr))
    {
        // Write the new location back to the object that needs the easing value.
        // This is needed because backfill_vector moves the elements after one is removed, so without
        // this objets that use the easing values would now point to the wrong location in the array.
        *item.base_props.back_reference = &item.base_props;
    }
}


public_func void
Easing_EngineRemove(Easing_Engine& engine, Easing_Float& value);


public_func void
Easing_EngineRemove(Easing_Float& value);


inline void
Easing_EngineIntegrate(Easing_Engine& engine, float dt)
{
    for (auto& item : engine.linear)
    {
        Easing_LinearIntegrate(item, dt);
    }
}


inline void
Easing_EngineIntegrate(float dt)
{
    Easing_EngineIntegrate(global_bfv, dt);
}
