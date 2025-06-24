#pragma once
#include "BankField.h"

class TaxField : public BankField {
public:
	TaxField(String name, FieldType type, int amount, String description);
	int applyEffect(Player& p) override;
	TaxField* clone() const override;
};