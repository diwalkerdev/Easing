#include "Easing/easing.h"
#include <cassert>
#include <stdio.h>
#include <vector>


void
test_make_debounce_switch_creates_one_element()
{
    easing::Easer easer;
    auto          debounce = make_debounce_switch(easer, 10);

    assert(easer.debouncers.size() == 1);
    assert(easer.debouncers[0].timeout_ms == 10);
}

void
test_make_debounce_switch_twice_creates_two_elements()
{
    easing::Easer easer;

    auto debounce = make_debounce_switch(easer, 10);
    auto other    = make_debounce_switch(easer, 10);

    assert(easer.debouncers.size() == 2);

    // Starts in default state.
    assert(easer.debouncers[0].state == easing::DebounceState::DEFAULT);

    // Set changes state to running.
    debounce.set(true);
    assert(easer.debouncers[0].state == easing::DebounceState::RUNNING);

    // Starts in default state.
    assert(easer.debouncers[1].state == easing::DebounceState::DEFAULT);
}

void
test_get_set_and_step_example()
{
    easing::Easer easer;
    auto          debounce = easing::make_debounce_switch(easer, 20);

    // Starts in default state.
    assert(easer.debouncers[0].state == easing::DebounceState::DEFAULT);

    // Set changes state to running.
    debounce.set(true);
    assert(easer.debouncers[0].state == easing::DebounceState::RUNNING);

    // Stepping decreases time.
    integrate(easer.debouncers, 10);
    assert(easer.debouncers[0].time_ms == 10);

    // Getting after set returns true.
    auto value = debounce.get();
    assert(easer.debouncers[0].state == easing::DebounceState::RUNNING_GOT);
    assert(value);

    // Getting for a second time returns false.
    auto value_2nd = debounce.get();
    assert(easer.debouncers[0].state == easing::DebounceState::RUNNING_GOT);
    assert(!value_2nd);

    // When time reaches zero enters default state.
    integrate(easer.debouncers, 10);
    assert(easer.debouncers[0].time_ms == 0);
    assert(easer.debouncers[0].state == easing::DebounceState::DEFAULT);

    // check does not decrement further.
    integrate(easer.debouncers, 100);
    assert(easer.debouncers[0].time_ms == 0);
}

void
debounce_main()
{
    test_make_debounce_switch_creates_one_element();
    test_make_debounce_switch_twice_creates_two_elements();
    test_get_set_and_step_example();
    printf("TEST easing::debounce PASSED\n");
}
