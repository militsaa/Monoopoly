#include "Card.h"

Card::Card(CardType type, String description) : type(type), description(description) {}

//
//String Card::getDescription() const
//{
//	return description;
//}

void Card::print() const
{
	std::cout << description << '\n';
}


