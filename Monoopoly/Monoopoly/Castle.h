#pragma once
#include "Mortgage.h"

class Castle :public Mortgage {
public:
	Castle(int price);
	void add() override;
};