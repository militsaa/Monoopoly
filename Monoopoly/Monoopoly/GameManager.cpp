#include "GameManager.h"
#include "BuildableProperty.h"
#include "Constants.h"

GameManager::GameManager()
{
	//TO DO?
}\

void GameManager::collectNeighbour(Vector<BuildableProperty*>& same, int baseInd) const
{
	BuildableProperty* base = static_cast<BuildableProperty*>(board.getFields()[baseInd]);
	Neighbourhood colour = base->getNeighbourhood();
	same.push_back(base);

	const int left = baseInd >= 2 ? baseInd - 2 : 0;
	const int right = baseInd + 2 < FIELDS_COUNT ? baseInd + 2 : FIELDS_COUNT - 1;

	for (int i = left; i <= right; ++i) {
		if (baseInd == i)
		{
			continue;
		}
		Field* curr = board.getFields()[i];
		if (curr->getType() != FieldType::PROPERTY) {
			continue;
		}

		BuildableProperty* pr = static_cast<BuildableProperty*>(curr);
		if (pr->getNeighbourhood() == colour) {
			same.push_back(pr);
		}
	}
}

bool GameManager::evenBuildRuleRespected(const Vector<BuildableProperty*>& sameNb) const
{
	const int baseInd = 0;
	for (size_t i = 1; i < sameNb.getSize(); i++)
	{
		if (sameNb[baseInd]->getCottageCount()> sameNb[i]->getCottageCount())
		{
			return false;
		}
	}
	return true;
}

bool GameManager::ownsWholeSet(const Vector<BuildableProperty*>& sameNb) const
{
	for (size_t i = 1; i < sameNb.getSize(); ++i) {
		if (!sameNb[i]->isOwnedBy(*players[currPlayer])) {
			return false;
		}
	}
	return true;
}

int GameManager::getFieldIndByName(String fieldName) const
{
	for (size_t i = 0; i < getFields().getSize(); i++)
	{
		if (getFields()[i]->getName()==fieldName)
		{
			return i;
		}
	}
	return -1;
}

bool GameManager::canBuildCottage(int fieldInd) const
{
	if (getFields()[fieldInd]->getType()!=FieldType::PROPERTY)
	{
		std::cout << "You can build only on properties!\n";
		return false;
	}

	BuildableProperty* prop = static_cast<BuildableProperty*>(board.getFields()[fieldInd]);

	if (!prop->isBought() || !prop->isOwnedBy(*players[currPlayer]) ||
		prop->getHasCastle() || prop->getCottageCount() != 4 || players[currPlayer]->getBalance() < prop->getCottagePrice())
		return false;

	Vector<BuildableProperty*> neighb;
	collectNeighbour(neighb, fieldInd);

	if (!ownsWholeSet(neighb)) {
		return false;
	}
	if (!evenBuildRuleRespected(neighb)) {
		return false;
	}

	return true;
}

GameManager& GameManager::getInstance()
{
	static GameManager instance;
	return instance;
}

Vector<Player*> GameManager::getPlayers() const
{
	return players;
}

Vector<Field*> GameManager::getFields() const
{
	return board.getFields();
}

void GameManager::buildCottage(String fieldName)
{
	int fieldInd = getFieldIndByName(fieldName);
	if (fieldInd<0)
	{
		std::cout << "There is no such field!\n";
		return;
	}
	if (!canBuildCottage(fieldInd))
	{
		std::cout << "You cannot build a cottage!\n";
		return;
	}
	BuildableProperty* prop = static_cast<BuildableProperty*>(board.getFields()[fieldInd]);
	prop->addCottage();
	std::cout << "Cottage is build successfully on "<< fieldName <<"!\n";
}



