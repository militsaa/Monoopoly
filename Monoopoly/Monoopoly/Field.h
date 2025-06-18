#pragma once
#include "SmallStringOpt.h"

enum class FieldType { PROPERTY, CARDFIELD, GOTOJAIL, JAIL, GO, PARKING, TAXFIELD };

class Field {
	FieldType type;
	String name;
public:
	Field(String name, FieldType type);
	virtual ~Field()= default;
	FieldType getType() const;
	String getName() const;
	//virtual Field* clone() const = 0;
};