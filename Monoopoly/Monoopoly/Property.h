#pragma once
#include "Field.h"
#include "Player.h"

enum PropertyType{
	BUILDABLE_PROPERTY, UTILITY, STATION
};

class Property :public Field {
protected:
	Player* owner = nullptr;
	PropertyType type;
	int price;

public:
	Property(String name, FieldType t, PropertyType type, int price);
	Property* clone() const override;
	bool isBought() const; //check if player is nullptr
	void buy(Player& player);
	Player* getOwner()const;
	void returnProperty();
	bool isOwnedBy(const Player& p) const;
	virtual int rent()const;
	//void payToOwner()
	/*void addCottage();
	bool hasMaxCottages() const;
	void replaceWithCastle();
	bool hasCastleBuilt() const;*/
};