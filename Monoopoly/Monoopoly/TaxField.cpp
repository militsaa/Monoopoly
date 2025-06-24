#include "TaxField.h"
#include "CommandReactFactory.h"

TaxField::TaxField(String name, FieldType type, int amount) : BankField(name, type, amount){}

void TaxField::applyEffect(Player& p)
{
	if (p.getBalance()>=amount)
	{
	p.giveMoney(amount);
	return;
	}
	else {
		std::cout << p.getUserName() << " You do not have enough money what would you like to do?\n";
		String command;
		bool rolled = false;
		bool justGotInPrison = false;
		int dept = 0;
		bool onTurn = false;
		dept = amount;
		while (dept > 0 && !p.isBankrupt())
		{
			std::cin >> command;
			CommandReactFactory::action(command, rolled, justGotInPrison, dept, onTurn);
			if (p.getBalance() >= amount)
			{
				p.giveMoney(amount);
				return;
			}
		}
	}
}

TaxField* TaxField::clone() const
{
	return new TaxField(*this);
}
