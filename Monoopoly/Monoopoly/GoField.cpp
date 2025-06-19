#include "GoField.h"

GoField::GoField(String name, FieldType type, int amount) : BankField(name, type, amount) {}

void GoField::applyEffect(Player& p)
{
	p.addMoney(amount);
}

GoField* GoField::clone() const
{
	return new GoField(*this);
}
