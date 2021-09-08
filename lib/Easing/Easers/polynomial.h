#pragma once
#include "Base/dllexports.h"
#include "Easing/float.h"


public_struct Easing_PolynomialProperties
{
    Easing_Properties base_props { Easing_Type::Polynomial };
    float             p1 { 0.f };
    float             p2 { 0.f };
};


template <>
inline auto
Easing_Cast<Easing_PolynomialProperties*>(Easing_Properties* properties) -> Easing_PolynomialProperties*
{
    if (properties->type == Easing_Type::Polynomial)
    {
        return (Easing_PolynomialProperties*)(properties);
    }
    else
    {
        return nullptr;
    }
}