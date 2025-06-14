#include "MovePositionCard.h"

MovePositionCard::MovePositionCard(CardType type, String description, int ind) : Card(type, description), index(ind) {}

void MovePositionCard::apply(Player& player) const
{
	player.setPosition(index);
}
