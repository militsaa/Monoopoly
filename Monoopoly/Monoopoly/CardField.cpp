#include "CardField.h"
#include "Card.h"

CardField::CardField(String name, FieldType type) : Field(name, type) {}

CardField* CardField::clone() const
{
	return new CardField(*this);
}

void CardField::drawAndApply(Player& player, int dept) const
{
	Card* currCard = deck.draw();
	currCard->applyEffect(player, dept);
}
