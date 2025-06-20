#include "DeadField.h"

DeadField::DeadField(String name, FieldType type) : Field(name, type) {}

DeadField* DeadField::clone() const
{
	return new DeadField(*this);
}
