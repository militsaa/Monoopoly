#pragma once  
#include "CardDeck.h"
#include "Field.h"

class CardField: public Field {
	static CardDeck deck;

public:
	CardField(String name, FieldType type);
	CardField* clone() const override;
	void drawAndApply(Player& player, int dept)const;
};