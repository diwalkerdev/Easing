#include "Base/containers/backfill_vector.hpp"
#include "Base/typedefs.h"
#include "Easing/base.h"
#include "Easing/engine.h"
#include <cassert>


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
        auto* item = Easing_Cast<Easing_PolynomialProperties>(ob_4.health);
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
        auto* item = Easing_Cast<Easing_PolynomialProperties>(ob_1.health);
        assert(item == nullptr);
    }

    {
        auto* item = Easing_Cast<Easing_Linear>(ob_2.health);
        assert(item);
        item->rate = 0.5;
    }

    {
        auto* item = Easing_Cast<Easing_PolynomialProperties>(ob_3.health);
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


void
Test_LinearEaser()
{
    printf("Test_LinearEaser\n");

    Easing_Float value;
    Easing_Init2<Easing_Linear>(value, 10.f, 0.f);

    auto* props = Easing_Cast<Easing_Linear>(value);
    assert(props);
    props->rate = 1.f;

    // Increase the value so it goes up to 5.
    Easing_EngineIntegrate(1000);
    printf("Value: %f\n", value.value());
    printf("Eased: %f\n", value.eased());

    Easing_EngineIntegrate(1000);
    printf("Value: %f\n", value.value());
    printf("Eased: %f\n", value.eased());

    Easing_EngineIntegrate(1000);
    Easing_EngineIntegrate(1000);
    Easing_EngineIntegrate(1000);

    // Then set the value to 0 to check that the eased value now decreases.
    value = 0.f;
    Easing_EngineIntegrate(1000);
    printf("Value: %f\n", value.value());
    printf("Eased: %f\n", value.eased());

    printf("Test_LinearEaser End\n");
}
