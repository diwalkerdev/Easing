#include "Easing/float.h"
#include "Easing/engine.h"

void
Easing_Init(Easing_Type type, Easing_Properties** values)
{
    Easing_Init(global_bfv, type, values);
}


void
Easing_Init(Easing_Type type, Easing_Float& value)
{
    Easing_Init(global_bfv, type, &value.base_props);
}


void
Easing_Init(Easing_Type type, Easing_Float& value, float init, float eased)
{
    Easing_Init(global_bfv, type, &value.base_props);
    value.base_props->values.value = init;
    value.base_props->values.eased = eased;
}


Easing_Float::Easing_Float(Easing_Type type)
{
    Easing_Init(type, &base_props);
};


Easing_Float::Easing_Float(Easing_Type type, float value)
{
    Easing_Init(type, &base_props);
    base_props->values.value = value;
    base_props->values.eased = 0;
};


Easing_Float::Easing_Float(Easing_Type type, float value, float eased)
{
    Easing_Init(type, &base_props);
    base_props->values.value = value;
    base_props->values.eased = eased;
};


Easing_Float::~Easing_Float()
{
    printf("~Easing_Float\n");
    Easing_EngineRemove(*this);
}