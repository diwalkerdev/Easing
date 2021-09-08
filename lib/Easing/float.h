#pragma once

#include "Base/dllexports.h"
#include "Easing/base.h"
#include <cassert>


public_struct Easing_Float
{
    Easing_Float() {};
    ~Easing_Float();


    Easing_Float(Easing_Float const& other) = delete;


    Easing_Float&
    operator=(Easing_Float const& other)
        = delete;


    Easing_Float(Easing_Float && other)
    {
        this->base_props                 = other.base_props;
        other.base_props->back_reference = &this->base_props;
        other.base_props                 = nullptr;
    }


    Easing_Float&
    operator=(Easing_Float&& other)
    {
        this->base_props                 = other.base_props;
        other.base_props->back_reference = &this->base_props;
        other.base_props                 = nullptr;
        return *this;
    }


    Easing_Float(Easing_Type type);


    Easing_Float(Easing_Type type, float value);


    Easing_Float(Easing_Type type, float value, float eased);


    Easing_Float& operator=(float value)
    {
        assert(base_props);
        base_props->values.value = value;
        return *this;
    }


    float
    value() const
    {
        return base_props->values.value;
    }


    float
    eased() const
    {
        return base_props->values.eased;
    }


    Easing_Properties* base_props { nullptr };
};


public_func void
Easing_Init(Easing_Type type, Easing_Properties** values);


public_func void
Easing_Init(Easing_Type type, Easing_Float& value);


public_func void
Easing_Init(Easing_Type type, Easing_Float& value, float init, float eased);


// An unspecialised function for casing an Easing_Properties to a specific easer
// property type.
// Diffferent types of easer, provide a specialisation of this function to check
// if the cast is valid before the case is performed.
template <typename Tp>
auto
Easing_Cast(Easing_Properties* properties) -> Tp
{
}


// This function provides the convience of getting the properties from an Easing_Float.
// It calls the Easing_Cast(Easing_Properties*) function above.
// Diffferent types of easer, provide a specialisation of the above function to check
// if the cast is valid before the case is performed.
template <typename Tp>
auto
Easing_Cast(Easing_Float& value) -> Tp*
{
    return Easing_Cast<Tp*>(value.base_props);
}


template <typename Tp>
void
Easing_Init2(Easing_Float& flt, float value, float eased)
{
    Easing_Init2<Tp>(flt, value, eased);
}