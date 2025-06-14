#include "Field.h"

Field::Field(String name, FieldType t) : name(name), type(t) {}

FieldType Field::getType() const
{
	return type;
}

String Field::getName() const
{
	return name;
}
