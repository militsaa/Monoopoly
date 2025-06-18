#include "DeadField.h"

DeadField::DeadField(String name, FieldType type, int tax) : Field(name, type), tax(tax) {}

DeadField* DeadField::clone() const
{
    return new DeadField(*this);
}


