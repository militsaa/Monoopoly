#pragma once
#include "BankField.h"

class TaxField : public BankField {
public:
	TaxField(String name, FieldType type, int amount);
	void applyEffect(Player& p, int& dept) override;
	TaxField* clone() const override;
};