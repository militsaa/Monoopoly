#include "GroupPaymentCard.h"
#include "Vector.h"
#include "Player.h"

void GroupPaymentCard::getMoneyFromOthers(GameManager& gm, Player& player) const
{
	for (size_t i = 0; i < gm.getPlayers().getSize(); i++)
	{
		if (gm.getPlayers()[i]->getUserName() != player.getUserName())
		{
			gm.getPlayers()[i]->giveMoney(amount);
			if (!gm.getPlayers()[i]->isBankrupt())
			{
				player.addMoney(amount);
				//giveAllHisPossetionsToPlayer????? if bankrupt
			}
		}
	}
}

void GroupPaymentCard::giveMoneyToOthers(GameManager& gm, Player& player) const
{
	int sum = -amount;
	player.giveMoney(gm.getPlayers().getSize() * sum);
	if (player.isBankrupt())
	{
		//handle Returning All Properties to the bank
		return;
	}
	for (size_t i = 0; i < gm.getPlayers().getSize(); i++)
	{
		if (gm.getPlayers()[i]->getUserName() != player.getUserName())
		{
			gm.getPlayers()[i]->addMoney(sum);
		}
	}
}

GroupPaymentCard::GroupPaymentCard(CardType type, String description, int amount) : Card(type, description), amount(amount) {}

void GroupPaymentCard::applyEffect(Player& player) const
{
	GameManager& gm = GameManager::getInstance();
	if (amount > 0)
	{
		getMoneyFromOthers(gm, player);
		return;
	}
	giveMoneyToOthers(gm, player);
}

GroupPaymentCard* GroupPaymentCard::clone() const
{
	return new GroupPaymentCard(*this);
}
