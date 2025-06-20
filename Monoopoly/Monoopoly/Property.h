#pragma once
#include "Field.h"
#include "Player.h"

enum Neighbourhood {
	BROWN, LIGTHBLUE, PINK, ORANGE, GREEN, RED, YELLOW, PURPLE, STATION, DARKBLUE, UTILITY
};

class Property :public Field {
	Neighbourhood neighbourhood;
	Player* owner = nullptr;
	int price;
	int baseRent=1;
	int houseCount;
	bool hasCastle = false;
	int housePrise;
	int castlePrice;

public:
	Property(String name, FieldType t, Neighbourhood n, int price, int baseRent);
	bool isBought() const; //check if player is nullptr
	void buy(Player& player);
	Property* clone() const override;
	Player* getOwner()const;
	void returnProperty();
	//void payToOwner()
	/*void addCottage();
	bool hasMaxCottages() const;
	void replaceWithCastle();
	bool hasCastleBuilt() const;*/
};