#pragma once 
#include "Card.h"
#include "GameManager.h"

class GroupPaymentCard : public Card {
	int amount;
	void getMoneyFromOthers(GameManager& gm, Player& player, int& dept) const;
	void giveMoneyToOthers(GameManager& gm, Player& player) const;
public:
	GroupPaymentCard(CardType type, String description, int amount);
	void applyEffect(Player& player, int& dept) const override;
	GroupPaymentCard* clone() const override;
};