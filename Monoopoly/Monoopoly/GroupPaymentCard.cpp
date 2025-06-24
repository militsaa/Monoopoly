#include "GroupPaymentCard.h"
#include "Vector.h"
#include "Player.h"
#include "CommandReactFactory.h"

int GroupPaymentCard::getMoneyFromOthers(GameManager& gm, Player& player) const
{
	for (size_t i = 0; i < gm.getPlayers().getSize(); i++)
	{
		if (gm.getPlayers()[i]->getUserName() != player.getUserName())
		{
			if (gm.getPlayers()[i]->getBalance() >= amount)
			{
				gm.getPlayers()[i]->giveMoney(amount);
				player.addMoney(amount);
				std::cout << gm.getPlayers()[i]->getUserName() << " paid!\n";
				continue;
			}
			else {
				std::cout << gm.getPlayers()[i]->getUserName() << " you do not have enough money what would you like to do?\n";
				String command;
				bool rolled = false;
				bool rolledOnce = true;
				bool justGotInPrison = false;
				int dept = amount;
				bool onTurn = false;
				dept = amount;
				while (dept > 0 && !gm.getPlayers()[i]->isBankrupt())
				{
					std::cin >> command;
					CommandReactFactory::action(command, rolled, rolledOnce, justGotInPrison, dept, onTurn);
					if (gm.getPlayers()[i]->getBalance() >= amount)
					{
						gm.getPlayers()[i]->giveMoney(amount);
						player.addMoney(amount);
						std::cout << gm.getPlayers()[i]->getUserName() << " paid successfully!\n";
						dept = 0;
						break;;
					}
				}
			}
		}
	}
	return 0;
}

void GroupPaymentCard::payOthers(GameManager& gm, Player& player, int sum) const
{
	player.giveMoney(sum);
	for (size_t i = 0; i < gm.getPlayers().getSize(); i++)
	{
		if (!gm.getPlayers()[i]->isBankrupt() && gm.getPlayers()[i]->getUserName() != player.getUserName())
		{
			gm.getPlayers()[i]->addMoney(-amount);
		}
	}
}

int GroupPaymentCard::giveMoneyToOthers(GameManager& gm, Player& player) const
{
	int sum = (-amount) * gm.getActivePlayerCnt();

	if (player.getBalance() >= sum)
	{
		payOthers(gm, player, sum);
		std::cout << "Paid everyone successfully!\n";
		return 0;
	}
	else {
		std::cout << player.getUserName() << " You do not have enough money what would you like to do?\n";
		String command;
		bool rolled = false;
		bool rolledOnce = true;
		bool justGotInPrison = false;
		int dept = 0;
		bool onTurn = false;
		dept = amount;
		while (dept > 0 && !player.isBankrupt())
		{
			std::cin >> command;
			CommandReactFactory::action(command, rolled, rolledOnce, justGotInPrison, dept, onTurn);
			if (player.getBalance() >= amount)
			{
				payOthers(gm, player,sum);
				std::cout << "Paid everyone successfully!\n";
				return 0;
			}
		}
	}
}



GroupPaymentCard::GroupPaymentCard(CardType type, String description, int amount) : Card(type, description), amount(amount) {}

int GroupPaymentCard::applyEffect(Player& player) const
{
	GameManager& gm = GameManager::getInstance();
	if (amount > 0)
	{
		return getMoneyFromOthers(gm, player);
	}
	return giveMoneyToOthers(gm, player);
}

GroupPaymentCard* GroupPaymentCard::clone() const
{
	return new GroupPaymentCard(*this);
}
