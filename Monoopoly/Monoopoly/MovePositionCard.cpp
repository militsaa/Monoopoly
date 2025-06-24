#include "MovePositionCard.h"
#include "Constants.h"
#include "GameManager.h"

MovePositionCard::MovePositionCard(CardType type, String description, int steps) : Card(type, description), steps(steps) {}

int MovePositionCard::applyEffect(Player& player) const
{
	GameManager& gm = GameManager::getInstance();
	player.movePosition(steps);
	return gm.stepOnNewField();
}

MovePositionCard* MovePositionCard::clone() const
{
	return new MovePositionCard(*this);
}




