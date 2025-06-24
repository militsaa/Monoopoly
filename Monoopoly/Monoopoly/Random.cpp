#include "Random.h"
#include <random>

int randomNumberGenerator(int size)           
{
    static std::mt19937 rng(std::random_device{}());      
    std::uniform_int_distribution<int> dist(0, size - 1);
    return dist(rng);
}

int dieGenerator(int size)                    
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, size);
    return dist(rng);
}