#include "Easing/easing.h"
#include "Easing/linear.h"
#include <cassert>

void
test_make_linear_creates_one_element()
{
    easing::Easer easer;
    auto          le = make_linear_easer(easer, 100, 10);

    assert(easer.linears.size() == 1);

    auto& item = easer.linears.back();

    assert(item.target_value == 100);
    assert(item.current_value == 100);
    assert(item.rate == 10);
    assert(item.state == easing::LinearState::Default);
    assert(item.ref_count == 1);
}

void
test_reset_changes_values_after_construction()
{
    easing::Easer easer;
    auto          le = make_linear_easer(easer, 100, 10);

    le.reset(1000, 42);

    assert(le.get() == 1000);

    auto& item = easer.linears.back();

    assert(item.target_value == 1000);
    assert(item.current_value == 1000);
    assert(item.rate == 42);
    assert(item.state == easing::LinearState::Default);
    assert(item.ref_count == 1);
}

void
test_set_integrate_example()
{
    easing::Easer easer;
    auto          le   = make_linear_easer(easer, 100, 10);
    auto&         item = easer.linears.back();

    le.set(80);

    assert(item.target_value == 80);
    assert(item.current_value == 100);
    assert(item.state == easing::LinearState::Running);

    // 500ms is half a second, so value should change by half rate.
    integrate_linear(item, 500.0);

    assert(item.target_value == 80);
    assert(item.current_value == 95);
    assert(item.state == easing::LinearState::Running);

    easing::integrate_linear(item, 500);
    assert(item.current_value == 90);

    // Integrate well past the target value.
    easing::integrate_linear(item, 2000);
    assert(item.current_value == 80);
    assert(item.state == easing::LinearState::Default);
}

void
linear_main()
{
    test_make_linear_creates_one_element();
    test_reset_changes_values_after_construction();
    test_set_integrate_example();
    printf("TEST easing::linear PASSED\n");
}