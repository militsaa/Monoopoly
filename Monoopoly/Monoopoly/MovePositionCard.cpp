#include "MovePositionCard.h"
#include "Constants.h"

MovePositionCard::MovePositionCard(CardType type, String description, int steps) : Card(type, description), steps(steps) {}

void MovePositionCard::applyEffect(Player& player) const
{
	player.movePosition(steps);
	int dept = gm.stepOnNewField(dept);
}

MovePositionCard* MovePositionCard::clone() const
{
	return new MovePositionCard(*this);
}




