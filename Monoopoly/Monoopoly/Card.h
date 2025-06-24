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
	void print() const;
	virtual int applyEffect(Player& player) const = 0;
	virtual Card* clone()const = 0;
};