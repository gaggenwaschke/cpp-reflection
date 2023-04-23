#pragma once

namespace mock
{
    struct Clown
    {
        int first;
        char second;
    };

    template <typename T>
    struct Tent
    {
        T value;
    };
} // namespace mock