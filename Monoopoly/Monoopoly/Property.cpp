#include "Property.h"

Property::Property(String name, FieldType t, Neighbourhood n, int price, int baseRent) : Field(name, t), neighbourhood(n), price(price), baseRent(baseRent) {}

bool Property::isBought() const
{
	return owner != nullptr;
}

void Property::buy(Player& player)
{
	//checck if its bought
	if (player.getBalance()>=price)
	{
		player.buyProp(price);
		owner = &player;
	}
	else {
		std::cout << "You don't have enough money to buy this property!" << "\n";
	}
}

Property* Property::clone() const
{
	return new Property(*this);
}

