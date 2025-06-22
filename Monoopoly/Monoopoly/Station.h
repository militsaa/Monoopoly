#pragma once
#include "Property.h"
#include "Player.h"

class Station :public Property {
	int baseRent;

public:
	Station(String name, FieldType field, PropertyType type);
	Station* clone() const override;
	int rent()const override;
};