#include "Easing/engine.h"

public_var Easing_Engine global_bfv;


void
Easing_Init(Easing_Engine& engine, Easing_Type type, Easing_Properties** values)
{
    Easing_Properties* item;
    switch (type)
    {
    case Easing_Type::Linear:
    {
        engine.linear.allocate();
        auto& linear_prop = engine.linear.back();
        item              = &linear_prop.base_props;
        break;
    }
    case Easing_Type::Polynomial:
    {
        engine.poly.allocate();
        auto& poly_prop = engine.poly.back();
        item            = &poly_prop.base_props;
        break;
    }
    }

    *values              = item;
    item->back_reference = values;
}

void
Easing_Free(Easing_Engine& engine)
{
    engine.linear.clear();
    engine.poly.clear();
}


void
Easing_EngineRemove(Easing_Engine& engine, Easing_Float& value)
{
    if (value.base_props == nullptr)
    {
        return;
    }

    switch (value.base_props->type)
    {
    case Easing_Type::Linear:
    {
        auto index = (int)(value.base_props - &engine.linear[0].base_props) / sizeof(Easing_Linear);
        Easing_EngineRemove(engine.linear, index);
        break;
    }
    case Easing_Type::Polynomial:
    {
        auto index = (int)(value.base_props - &engine.poly[0].base_props) / sizeof(Easing_PolynomialProperties);
        Easing_EngineRemove(engine.poly, index);
        break;
    }
    }
}

void
Easing_EngineRemove(Easing_Float& value)
{
    Easing_EngineRemove(global_bfv, value);
}