#include <ctime>
#include <cstdio>
#include <cstdlib>

int closest_weight(int value);
int brute_force(int value);
int hamming_weight(int value);

int main()
{
    srand(time(0));
    for (int j = 1; j < 25; ++j)
    {
        int random_int = rand() % 900 + 100;
        int bit_calc = closest_weight(random_int);
        int brute_calc = brute_force(random_int);
        std::printf("value is: %i\n", random_int);
        std::printf("bit calculation: %i\n", bit_calc);
        std::printf("brute force calc: %i\n", brute_calc);
    }

    return 0;
}

int closest_weight(int value)
{
    int mask = 1;

    bool first_bit = (value & mask) != 0 ? true : false;

    mask <<= 1;

    bool next_bit = (value & mask) != 0 ? true : false;

    while (first_bit == next_bit)
    {
        mask <<= 1;
        first_bit = next_bit;
        next_bit = (value & mask) != 0 ? true : false;
    }

    mask |= mask >> 1;

    return value ^ mask;
}

int brute_force(int value)
{
    int weight = hamming_weight(value);

    int step = 1;

    while (true)
    {
        if (hamming_weight(value - step) == weight)
            return value - step;

        else if (hamming_weight(value + step) == weight)
            return value + step;

        step += 1;
    }
}
int hamming_weight(int value)
{
    int count = 0;
    int mask = 1;

    while (mask <= value)
    {
        if (value & mask)
        {
            count += 1;
        }
        mask <<= 1;
    }

    return count;
}
