#pragma once
#include "SmallStringOpt.h"

enum class FieldType {PROPERTY, CARDFIELD, GOTOJAIL, JAIL, GO, PARKING, TAXFIELD};

class Field {
	FieldType type;
	String name;
public:
	Field(String name, FieldType type);
	FieldType getType() const;
	String getName() const;
};