#pragma once
#include "Field.h"
#include "Player.h"
#include "Castle.h"
#include "Cottage.h"

enum Neighbourhood {
	BLUE, GREEN, RED, PINK, ORANGE, YELLOW, PURPLE, BROWN, STATION,DARKBLUE, UTILITY, STATION
};

class Property :public Field {
	Player* owner = nullptr;
	int price;
	int baseRent;
	Neighbourhood neighbourhood;
	//Cottage cottages;
	//Castle castles;

public:
	Property(String name, FieldType t, Neighbourhood n, int price, int baseRent);
	bool isBought() const; //check if player is nullptr
	void buy(Player& player);
	//void payToOwner()
};