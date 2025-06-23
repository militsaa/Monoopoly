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
	~Property() = default;
	Property* clone() const override;
	bool isBought() const; //check if player is nullptr
	void buy(Player& player);
	Player* getOwner()const;
	void setOwner(Player*);
	int getPrice() const;
	void returnProperty();
	bool isOwnedBy(const Player& p) const;
	PropertyType getPropertyType() const;
	virtual int rent()const;
	int stepedOnProp()const;
};