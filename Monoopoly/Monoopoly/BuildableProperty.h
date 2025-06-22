#pragma once
#include "Property.h"
#include "Player.h"

enum class Neighbourhood {
	BROWN, LIGTHBLUE, PINK, ORANGE, GREEN, RED, YELLOW, DARKBLUE
};

class BuildableProperty :public Property {
	Neighbourhood neighbourhood;
	int baseRent;
	int cottageCount = 0;
	bool hasCastle = false;

public:
	BuildableProperty(String name, FieldType field, PropertyType type, int price, Neighbourhood n, int baseRent);
	BuildableProperty* clone() const override;
	void addCottage();
	void replaceWithCastle();
	bool getHasCastle() const;
	int getCottageCount() const;
	Neighbourhood getNeighbourhood()const;
	int getCottagePrice() const;
	int rent()const override;
	//void payToOwner()
	/*void addCottage();
	bool hasMaxCottages() const;
	void replaceWithCastle();
	bool hasCastleBuilt() const;*/
};