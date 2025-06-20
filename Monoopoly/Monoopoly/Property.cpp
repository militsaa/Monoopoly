#include "Property.h"

Property::Property(String name, FieldType t, Neighbourhood n, int price, int baseRent) : Field(name, t), neighbourhood(n), price(price), baseRent(baseRent){}

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

Player* Property::getOwner() const
{
	return owner;
}

void Property::returnProperty()
{
	owner = nullptr;
}

void Property::addCottage()
{
	cottageCount++;
}

void Property::replaceWithCastle()
{
	cottageCount = 0;
	hasCastle = true;
}

bool Property::isOwnedBy(const Player& p) const
{
	return owner == &p;
}

bool Property::getHasCastle() const
{
	return cottageCount;
}

int Property::getCottageCount() const
{
	return cottageCount;
}

Neighbourhood Property::getNeighbourhood() const
{
	return neighbourhood;
}

int Property::getCottagePrice() const
{
	switch (neighbourhood)
	{
	case BROWN:
	case LIGTHBLUE:
		return 50;
		break;
	case PINK:
	case ORANGE:
		return 100;
		break;
	case YELLOW:
	case RED:
		return 150;
		break;
	case GREEN:
	case DARKBLUE:
		return 200;
		break;
	default:
		return 0;
		break;
	}
}

