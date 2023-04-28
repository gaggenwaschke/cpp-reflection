#pragma once

namespace mock
{
    struct Clown
    {
        int first;
        char second;
    };

    struct Car
    {
        int speed;
        short fuel;
        char passengers;
    };

    template <typename T>
    struct Tent
    {
        T value;
    };
} // namespace mock