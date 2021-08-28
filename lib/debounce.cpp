#include "easing/debounce.h"
#include "Base/dllexports.h"


void
easing::integrate_debounce(easing::DebounceData& data, float ms)
{
    if (data.state != easing::DebounceState::DEFAULT)
    {
        data.time_ms -= ms;
        if (data.time_ms <= 0)
        {
            data.state = easing::DebounceState::DEFAULT;
        }
    }
}

easing::Debounce::~Debounce()
{
    if (data)
    {
        data->ref_count -= 1;
    }
}

easing::Debounce::Debounce(Debounce const& other)
    : data(other.data)
{
    data->ref_count += 1;
}

auto
easing::Debounce::operator=(Debounce const& other) -> Debounce&
{
    data = other.data;
    data->ref_count += 1;
    return *this;
}

auto
easing::Debounce::get() -> bool
{
    switch (data->state)
    {
    case DebounceState::RUNNING: {
        data->state = DebounceState::RUNNING_GOT;
        return true;
    }
    default: {
        return false;
    }
    }
}

auto
easing::Debounce::set(bool value) -> bool
{
    if (!value)
    {
        return false;
    }

    switch (data->state)
    {
    case DebounceState::DEFAULT: {
        data->state   = DebounceState::RUNNING;
        data->time_ms = data->timeout_ms;
        return true;
    }
    default: {
        return false;
    }
    }
}
