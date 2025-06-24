#pragma once
#include "Card.h"

class MovePositionCard : public Card {
	int steps;
	//bool shouldCollectGo;
public:
	MovePositionCard(CardType type, String description, int steps);
	void applyEffect(Player& player,) const override;
	MovePositionCard* clone() const override;
};
