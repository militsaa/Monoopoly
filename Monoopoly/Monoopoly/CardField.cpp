#include "CardField.h"
#include "Card.h"

CardDeck CardField::deck;

CardField::CardField(String name, FieldType type) : Field(name, type) {}

CardField* CardField::clone() const
{
	return new CardField(*this);
}

void CardField::drawAndApply(Player& player) const
{
	Card* currCard = deck.draw();
	currCard->print();
	currCard->applyEffect(player);
}
