#include "GoField.h"

GoField::GoField(String name, FieldType type, int amount, String description) : BankField(name, type, amount,description) {}

int GoField::applyEffect(Player& p)
{
	p.addMoney(amount);
	return 0;
}

GoField* GoField::clone() const
{
	return new GoField(*this);
}
