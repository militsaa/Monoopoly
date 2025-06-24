#include "PaymentCard.h"
#include "CommandReactFactory.h"

PaymentCard::PaymentCard(CardType type, String description, int amount) : Card(type, description), amount(amount) {}

int PaymentCard::applyEffect(Player& player) const
{
	if (amount > 0)
	{
		player.addMoney(amount);
		return 0;
	}
	if (player.getBalance() >= (-amount))
	{
		player.giveMoney(-amount);
		std::cout << "Paid successfully!\n";
		return 0;
	}
	else
	{
		std::cout << player.getUserName() << " You do not have enough money what would you like to do?\n";
		String command;
		bool rolled = false;
		bool rolledOnce = true;
		bool justGotInPrison = false;
		int dept = -amount;
		bool onTurn = false;
		dept = amount;
		while (dept > 0 && !player.isBankrupt())
		{
			std::cin >> command;
			CommandReactFactory::action(command, rolled, rolledOnce, justGotInPrison, dept, onTurn);
			if (player.getBalance() >= ( - amount))
			{
				player.giveMoney(-amount);
				return 0;
			}
		}
		return 0;
	}
}

PaymentCard* PaymentCard::clone() const
{
	return new PaymentCard(*this);
}
