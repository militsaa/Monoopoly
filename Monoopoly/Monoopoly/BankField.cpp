#include "BankField.h"

BankField::BankField(String name, FieldType type, int am, String description) : Field(name, type), amount(am), description(description){}

int BankField::getAmount() const
{
	return amount;
}

String BankField::getDescription() const
{
	return description;
}
