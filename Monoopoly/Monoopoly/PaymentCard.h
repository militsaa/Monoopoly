#pragma once 
#include "Card.h"

class PaymentCard: public Card {
	int amount;
public:
	PaymentCard(CardType type, String description, int amount);
	void apply(Player& player) const override;
};