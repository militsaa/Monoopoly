#include "TaxField.h"
#include "CommandReactFactory.h"

TaxField::TaxField(String name, FieldType type, int amount, String description) : BankField(name, type, amount, description) {}

int TaxField::applyEffect(Player& p)
{
	if (p.getBalance() >= amount)
	{
		p.giveMoney(amount);
		return 0;
	}
	std::cout << p.getUserName() << " You do not have enough money what would you like to do?\n";
	return amount;
}

TaxField* TaxField::clone() const
{
	return new TaxField(*this);
}
