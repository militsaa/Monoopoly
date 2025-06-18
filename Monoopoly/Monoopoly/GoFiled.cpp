#include "GoFiled.h"

GoField::GoField(String name, FieldType type):BankField(name, type)
{
	amount = 200;
}

void GoField::applyEffect(Player& p)
{
	p.addMoney(amount);
}
