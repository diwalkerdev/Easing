#pragma once
#include "Base/dllexports.h"
#include "Easing/float.h"
#include <algorithm>
#include <cmath>


public_struct Easing_Linear
{
    Easing_Properties base_props { Easing_Type::Linear };
    float             rate { 0.f };
};


template <>
inline void
Easing_Init<Easing_Linear>(Easing_Float& flt, float value, float eased)
{
    Easing_Init(Easing_Type::Linear, flt, value, eased);
}


inline void
Easing_LinearIntegrate(Easing_Linear& linear, float ms)
{
    auto& value = linear.base_props.values.value;
    auto& eased = linear.base_props.values.eased;
    auto  rate  = linear.rate;

    if (eased < value)
    {
        auto const diff      = value - eased;
        auto const increment = std::min(rate * (ms / 1000.f), diff);
        linear.base_props.values.eased += increment;
    }
    else
    {
        auto const diff      = eased - value;
        auto const increment = std::min(rate * (ms / 1000.f), diff);
        linear.base_props.values.eased -= increment;
    }
}


// Specialisations don't require the template parameter, and are therefore fully defined.
// To prevent multiple definition errors, they need to be inlined.
template <>
inline auto
Easing_Cast<Easing_Linear*>(Easing_Properties* properties) -> Easing_Linear*
{
    if (properties->type == Easing_Type::Linear)
    {
        return (Easing_Linear*)(properties);
    }
    else
    {
        return nullptr;
    }
}