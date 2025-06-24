#include "Property.h"
#include "GameManager.h"
#include "Constants.h"

Property::Property(String name, FieldType t, PropertyType type, int price) : Field(name, t), type(type), price(price) {}

Property* Property::clone() const
{
	return new Property(*this);
}

bool Property::isBought() const
{
	return owner != nullptr;
}

void Property::buy(Player& player)
{
	if (isBought())
	{
		std::cout << "Already bought!\n";
		return;
	}
	if (player.buyProp(price))
	{
		std::cout << "Buyed successfully!\n";
		owner = &player;
	}
	else {
		std::cout << "You don't have enough money to buy this property!" << "\n";
	}
}

Player* Property::getOwner() const
{
	return owner;
}

void Property::setOwner(Player* player)
{
	owner = player;
}

int Property::getPrice() const
{
	return price;
}


void Property::returnProperty()
{
	owner = nullptr;
}

bool Property::isOwnedBy(const Player* p) const
{
	return p == owner;
}

PropertyType Property::getPropertyType() const
{
	return type;
}

int Property::rent() const
{
	GameManager& gm = GameManager::getInstance();
	Property* fstUtility = static_cast<Property*>(gm.getFields()[ELECTRIC_COMPANY_IND]);
	Property* secUtility = static_cast<Property*>(gm.getFields()[WATER_WORKS_IND]);

	if (fstUtility->getOwner() == secUtility->getOwner())
	{
		return 10;
	}
	return 4;
}

int Property::stepedOnProp() const
{
	if (!isBought())
	{
		std::cout << "You can buy this property if you want! (" << price << ")\n";
		return 0;
	}
	return rent();
}

