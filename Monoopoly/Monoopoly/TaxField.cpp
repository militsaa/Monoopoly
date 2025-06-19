#include "TaxField.h"

TaxField::TaxField(String name, FieldType type, int amount) : BankField(name, type, amount){}

void TaxField::applyEffect(Player& p)
{
	p.giveMoney(amount);
}

TaxField* TaxField::clone() const
{
	return new TaxField(*this);
}
