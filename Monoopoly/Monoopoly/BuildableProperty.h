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
	void addCastle();
	void replaceWithCastle();
	bool getHasCastle() const;
	void sellCastle();
	int getCottageCount() const;
	void sellCottages(int count);
	Neighbourhood getNeighbourhood()const;
	int getCottagePrice() const;
	int rent()const override;
};