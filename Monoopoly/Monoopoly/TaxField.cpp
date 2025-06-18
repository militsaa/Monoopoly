#include "TaxField.h"

TaxField::TaxField(String name, FieldType type, int amount) : BankField(name, type, amount){}

void TaxField::applyEffect(Player& p)
{
}
