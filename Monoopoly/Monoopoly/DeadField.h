#pragma once
#include "Field.h"

class DeadField :public Field {
	int tax;
public:
	DeadField(String name, FieldType type, int tax);
	//DeadField* clone() const override;
};