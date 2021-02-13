
#include "easing/debounce.h"

using namespace easing;

Debounce::Debounce(DebounceData& item)
    : data(item)
{
    ++data.ref_count;
}

Debounce::~Debounce()
{
    --data.ref_count;
}

Debounce::Debounce(Debounce const& other)
    : data(other.data)
{
    ++data.ref_count;
}

auto Debounce::operator=(Debounce const& other) -> Debounce&
{
    data = other.data;
    ++data.ref_count;
    return *this;
}

auto Debounce::get() -> bool
{
    switch (data.state)
    {
    case DebounceState::RUNNING: {
        data.state = DebounceState::RUNNING_GOT;
        return true;
    }
    default: {
        return false;
    }
    }
}

auto Debounce::set(bool value) -> bool
{
    if (!value)
    {
        return false;
    }

    switch (data.state)
    {
    case DebounceState::DEFAULT: {
        data.state   = DebounceState::RUNNING;
        data.time_ms = data.timeout_ms;
        return true;
    }
    default: {
        return false;
    }
    }
}

void integrate_debounce(DebounceData& data, float ms)
{
    if (data.state != DebounceState::DEFAULT)
    {
        data.time_ms -= ms;
        if (data.time_ms <= 0)
        {
            data.state = DebounceState::DEFAULT;
        }
    }
}