#pragma once
#include "Field.h"

class DeadField :public Field {
public:
	DeadField(String name, FieldType type);
	DeadField* clone() const override;
};