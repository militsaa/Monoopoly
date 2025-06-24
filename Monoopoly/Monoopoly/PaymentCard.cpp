#include "PaymentCard.h"

PaymentCard::PaymentCard(CardType type, String description, int amount) : Card(type, description), amount(amount){}

void PaymentCard::applyEffect(Player& player, int& dept) const
{
	if (amount>0)
	{
		player.addMoney(amount);
		return;
	}
	player.giveMoney(-amount);
}

PaymentCard* PaymentCard::clone() const
{
	return new PaymentCard(*this);
}
