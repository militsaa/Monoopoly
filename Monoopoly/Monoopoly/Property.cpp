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
	if (player.getBalance() >= price)
	{
		player.buyProp(price);
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

void Property::returnProperty()
{
	owner = nullptr;
}

bool Property::isOwnedBy(const Player& p) const
{
	return owner == &p;
}

int Property::rent() const
{
	GameManager& gm = GameManager::getInstance();
	Property* fstUtility = static_cast<Property*>(gm.getFields()[ELECTRIC_COMPANY_IND]);
	Property* secUtility = static_cast<Property*>(gm.getFields()[WATER_WORKS_IND]);

	if (fstUtility->getOwner() == secUtility->getOwner())
	{
		//to do die*10  else 4*die
		return 0;
	}
}
