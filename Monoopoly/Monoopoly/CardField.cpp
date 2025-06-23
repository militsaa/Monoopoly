#include "CardField.h"

CardField::CardField(String name, FieldType type) : Field(name, type) {}

CardField* CardField::clone() const
{
	return new CardField(*this);
}
