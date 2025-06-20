#include "Random.h"
#include <random>

int randomNumberGenerator(int size)
{
	srand(time(NULL));
	int number = rand() % (size);
	return number;
}