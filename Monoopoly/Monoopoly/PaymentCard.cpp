#include "PaymentCard.h"

PaymentCard::PaymentCard(CardType type, String description, int amount) : Card(type, description), amount(amount){}

void PaymentCard::apply(Player& player) const
{
	//check if player has the amount
	//player.payOrGet(amount);
}
