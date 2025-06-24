#include "Card.h"

Card::Card(CardType type, String description) : type(type), description(description) {}

void Card::print() const
{
	std::cout << description << '\n';
}


