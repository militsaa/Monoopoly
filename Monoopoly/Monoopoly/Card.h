#pragma once
#include "SmallStringOpt.h"
#include "Player.h"

enum class CardType {
	MOVE, PAY, GROUP_PAVEMENT
};
//doesnt need enum!!!!!

class Card {
	CardType type;
	String description;

public:

	Card(CardType type, String description);
	~Card() = default;
	virtual void applyEffect(Player& player) const = 0;
	virtual Card* clone()const = 0;
};