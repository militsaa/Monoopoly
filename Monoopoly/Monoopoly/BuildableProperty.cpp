#include "BuildableProperty.h"
#include "GameManager.h"
#include "Constants.h"

BuildableProperty::BuildableProperty(String name, FieldType field, PropertyType type, int price, Neighbourhood n, int baseRent) : Property(name, field, type,price), neighbourhood(n), baseRent(baseRent){}

BuildableProperty* BuildableProperty::clone() const
{
	return new BuildableProperty(*this);
}

void BuildableProperty::addCottage()
{
	cottageCount++;
}

void BuildableProperty::addCastle()
{
	cottageCount = 0;
	hasCastle = true;
}

void BuildableProperty::replaceWithCastle()
{
	cottageCount = 0;
	hasCastle = true;
}

bool BuildableProperty::getHasCastle() const
{
	return cottageCount;
}

void BuildableProperty::sellCastle()
{
	hasCastle = false;
}

int BuildableProperty::getCottageCount() const
{
	return cottageCount;
}

void BuildableProperty::sellCottages(int count)
{
	if (cottageCount>=count)
	{
		cottageCount -= count; 
		return;
	}
	cottageCount = 0;
}

Neighbourhood BuildableProperty::getNeighbourhood() const
{
	return neighbourhood;
}

int BuildableProperty::getCottagePrice() const
{
	switch (neighbourhood)
	{
	case Neighbourhood::BROWN:
	case Neighbourhood::LIGTHBLUE:
		return 50;
		break;
	case Neighbourhood::PINK:
	case Neighbourhood::ORANGE:
		return 100;
		break;
	case Neighbourhood::YELLOW:
	case Neighbourhood::RED:
		return 150;
		break;
	case Neighbourhood::GREEN:
	case Neighbourhood::DARKBLUE:
		return 200;
		break;
	default:
		return 0;
		break;
	}
}

int BuildableProperty::rent() const
{
	if (!hasCastle && !cottageCount)
	{
		return baseRent;
	}
	else if (hasCastle)
	{
		return baseRent * FOUR_COTTAGES_FACTOR * CASTLE_FACTOR;
	}
	double rent = baseRent;
	for (size_t i = 0; i < cottageCount; i++)
	{
		rent *= (1+COTTAGE_FACTOR);
	}
	return rent;
} // mai ne e dobre
