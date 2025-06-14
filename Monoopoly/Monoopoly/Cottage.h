#pragma once
#include "Mortgage.h"

class Cottage : public Mortgage {
public:
	Cottage(int price);
	void add() override;
};

