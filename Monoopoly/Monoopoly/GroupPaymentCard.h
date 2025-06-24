#pragma once 
#include "Card.h"
#include "GameManager.h"

class GroupPaymentCard : public Card {
	int amount;
	int getMoneyFromOthers(GameManager& gm, Player& player) const;
	int giveMoneyToOthers(GameManager& gm, Player& player) const;
	void payOthers(GameManager& gm, Player& player, int sum) const;

public:
	GroupPaymentCard(CardType type, String description, int amount);
	int applyEffect(Player& player) const override;
	GroupPaymentCard* clone() const override;
};