#pragma once
#include "Field.h"
#include "Player.h"

enum Neighbourhood {
	BROWN, LIGTHBLUE, PINK, ORANGE, GREEN, RED, YELLOW, STATION, DARKBLUE, UTILITY
};

class Property :public Field {
	Neighbourhood neighbourhood;
	Player* owner = nullptr;
	int price;
	int baseRent = 1;
	int cottageCount = 0;
	bool hasCastle = false;

public:
	Property(String name, FieldType t, Neighbourhood n, int price, int baseRent);
	bool isBought() const; //check if player is nullptr
	void buy(Player& player);
	Property* clone() const override;
	Player* getOwner()const;
	void returnProperty();
	void addCottage();
	void replaceWithCastle();
	bool isOwnedBy(const Player& p) const;
	bool getHasCastle() const;
	int getCottageCount() const;
	Neighbourhood getNeighbourhood()const;
	int getCottagePrice() const;
	//void payToOwner()
	/*void addCottage();
	bool hasMaxCottages() const;
	void replaceWithCastle();
	bool hasCastleBuilt() const;*/
};