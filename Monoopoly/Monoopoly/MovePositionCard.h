#pragma once
#include "Card.h"

class MovePositionCard : public Card {
	int index;
public:
	MovePositionCard(CardType type, String description, int index);
	void apply(Player& player) const override;
};

//TODO: THE LOGIC BEHIND BUILDING THEN SELLING MORTGAGE AND TRADING 