#pragma once

template<typename First, typename ... T>
bool is_in(First &&first, T && ... t)
{
    return ((first == t) || ...);
}

