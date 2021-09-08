#include "Base/containers/backfill_vector.hpp"
#include "Base/typedefs.h"
#include <cassert>


struct Easing_Values;


struct Easing_Values
{
    float value;
    float eased;
};


enum class Easing_Type
{
    Linear,
    Polynomial
};


struct Easing_Properties
{
    Easing_Type const   type;
    Easing_Properties** back_reference { nullptr };
    Easing_Values       values;

    Easing_Properties(Easing_Type type)
        : type(type)
    {
    }

    Easing_Properties(Easing_Properties&& other)
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


struct Easing_LinearProperties
{
    Easing_Properties base_props { Easing_Type::Linear };
    float             rate { 0.f };
};


struct Easing_PolynomialProperties
{
    Easing_Properties base_props { Easing_Type::Polynomial };
    float             p1 { 0.f };
    float             p2 { 0.f };
};


template <typename Tp>
auto
Easing_Cast(Easing_Properties* properties) -> Tp
{
}


template <>
auto
Easing_Cast<Easing_LinearProperties*>(Easing_Properties* properties) -> Easing_LinearProperties*
{
    if (properties->type == Easing_Type::Linear)
    {
        return (Easing_LinearProperties*)(properties);
    }
    else
    {
        return nullptr;
    }
}


template <>
auto
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


struct Easing_Engine
{
    backfill_vector<Easing_LinearProperties, 10>     linear;
    backfill_vector<Easing_PolynomialProperties, 10> poly;
    ~Easing_Engine()
    {
        printf("~Easing_Engine\n");
    }
} global_bfv;


void
Easing_Init(Easing_Engine& engine, Easing_Type type, Easing_Properties** values)
{
    Easing_Properties* item;
    switch (type)
    {
    case Easing_Type::Linear: {
        engine.linear.allocate();
        auto& linear_prop = engine.linear.back();
        item              = &linear_prop.base_props;
        break;
    }
    case Easing_Type::Polynomial: {
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
Easing_Init(Easing_Type type, Easing_Properties** values)
{
    Easing_Init(global_bfv, type, values);
}


struct Easing_Float
{
    Easing_Float() {};
    ~Easing_Float();


    Easing_Float(Easing_Float const& other) = delete;


    Easing_Float&
    operator=(Easing_Float const& other)
        = delete;


    Easing_Float(Easing_Float&& other)
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


    Easing_Float(Easing_Type type)
    {
        Easing_Init(type, &base_props);
    };


    Easing_Float(Easing_Type type, float value)
    {
        Easing_Init(type, &base_props);
        base_props->values.value = value;
        base_props->values.eased = 0;
    };


    Easing_Float(Easing_Type type, float value, float eased)
    {
        Easing_Init(type, &base_props);
        base_props->values.value = value;
        base_props->values.eased = eased;
    };


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


template <typename Tp>
auto
Easing_Cast(Easing_Float& value) -> Tp
{
    return Easing_Cast<Tp>(value.base_props);
}


void
Easing_Init(Easing_Type type, Easing_Float& value)
{
    Easing_Init(global_bfv, type, &value.base_props);
}


template <typename Tp>
void
Easing_EngineRemove(Tp& container, int index)
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


void
Easing_EngineRemove(Easing_Engine& engine, Easing_Float& value)
{
    if (value.base_props == nullptr)
    {
        return;
    }

    switch (value.base_props->type)
    {
    case Easing_Type::Linear: {
        auto index = (int)(value.base_props - &engine.linear[0].base_props) / sizeof(Easing_LinearProperties);
        Easing_EngineRemove(engine.linear, index);
        break;
    }
    case Easing_Type::Polynomial: {
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


Easing_Float::~Easing_Float()
{
    printf("~Easing_Float\n");
    Easing_EngineRemove(*this);
}


struct GameObject
{
    cstring      name;
    Easing_Float health;

    // ~GameObject()
    // {
    //     printf("~GameObject: %s\n", this->name);
    // }
};


GameObject
MakeGameObject()
{
    GameObject ob { "ob_4" };
    Easing_Init(Easing_Type::Polynomial, ob.health);
    return std::move(ob);
}


void
Test_RemoveItems()
{
    global_bfv.linear.allocate();
    global_bfv.linear.allocate();

    GameObject ob_1 { "ob_1" };
    GameObject ob_2 { "ob_2" };
    GameObject ob_3 { "ob_3" };
    // Should not compile.
    // GameObject ob_4 = ob_3;

    // Requires move constructors to work.
    auto ob_4 = MakeGameObject();
    {
        auto* item = Easing_Cast<Easing_PolynomialProperties*>(ob_4.health);
        assert(item);
        item->p1 = 0.2;
    }

    Easing_Init(Easing_Type::Linear, ob_1.health);
    Easing_Init(Easing_Type::Linear, ob_2.health);
    Easing_Init(Easing_Type::Polynomial, ob_3.health);


    printf("Ob1 health: %f\n", ob_1.health.value());
    printf("Ob2 health: %f\n", ob_2.health.value());
    for (auto& item : global_bfv.linear)
    {
        printf("Back ref: %p\n", item.base_props.back_reference);
        printf("Rate: %f\n", item.rate);
    }
    printf("\n");
    printf("\n");

    Easing_EngineRemove(global_bfv.linear, 2);

    printf("Ob2 health: %f\n", ob_2.health.value());

    {
        // Casting to wrong type should give nullptr.
        auto* item = Easing_Cast<Easing_PolynomialProperties*>(ob_1.health);
        assert(item == nullptr);
    }

    {
        auto* item = Easing_Cast<Easing_LinearProperties*>(ob_2.health);
        assert(item);
        item->rate = 0.5;
    }

    {
        auto* item = Easing_Cast<Easing_PolynomialProperties*>(ob_3.health);
        assert(item);
        item->p1 = 0.75;
    }


    printf("Print Linear\n");
    for (auto& item : global_bfv.linear)
    {
        printf("Back ref: %p\n", item.base_props.back_reference);
        printf("Rate: %f\n", item.rate);
    }
    printf("\n");
    printf("\n");

    printf("Print Poly\n");
    for (auto& item : global_bfv.poly)
    {
        printf("Back ref: %p\n", item.base_props.back_reference);
        printf("Rate: %f\n", item.p1);
    }
}
