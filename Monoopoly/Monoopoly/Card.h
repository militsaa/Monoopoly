#pragma once
#include "SmallStringOpt.h"
#include "Player.h"

enum class CardType {
	MOVE, PAY, GROUP_PAVEMENT
};

class Card {
	CardType type;
	String description;

public:
	Card(CardType type, String description);
	~Card() = default;
	virtual void apply(Player& player) const = 0;
};