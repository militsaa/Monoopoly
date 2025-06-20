#pragma once 
#include "Card.h"

class PaymentCard: public Card {
	int amount;
public:
	PaymentCard(CardType type, String description, int amount);
	void applyEffect(Player& player) const override;
	PaymentCard* clone() const override;
};