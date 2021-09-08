#pragma once

struct Easing_Values;


public_struct Easing_Values
{
    float value;
    float eased;
};


enum class Easing_Type
{
    Linear,
    Polynomial
};


public_struct Easing_Properties
{
    Easing_Type const   type;
    Easing_Properties** back_reference { nullptr };
    Easing_Values       values;

    Easing_Properties(Easing_Type type)
        : type(type)
    {
    }

    Easing_Properties(Easing_Properties && other)
        : type(other.type)
    {
        this->back_reference = other.back_reference;
        this->values         = other.values;
    }

    Easing_Properties&
    operator=(Easing_Properties&& other)
    {
        this->back_reference = other.back_reference;
        this->values         = other.values;
        return *this;
    }
};
