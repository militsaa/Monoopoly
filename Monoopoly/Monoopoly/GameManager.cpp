#include "GameManager.h"
#include "BuildableProperty.h"
#include "Constants.h"

GameManager::GameManager()
{
	//TODO?
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
		if (sameNb[baseInd]->getCottageCount() > sameNb[i]->getCottageCount())
		{
			return false;
		}
	}
	return true;
}

bool GameManager::readyForCastle(Vector<BuildableProperty*> neighb) const
{
	for (size_t i = 0; i < neighb.getSize(); i++)
	{
		if (neighb[i]->getCottageCount() != 4)
		{
			return false;
		}
	}return true;
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

int GameManager::getFieldIndByName(const String& fieldName) const
{
	for (size_t i = 0; i < getFields().getSize(); i++)
	{
		if (getFields()[i]->getName() == fieldName)
		{
			return i;
		}
	}
	return -1;
}

int GameManager::getPlayerIndByName(const String& username) const
{
	for (size_t i = 0; i < players.getSize(); i++)
	{
		if (players[i]->getUserName() == username)
		{
			return i;
		}
	}
	return -1;
}

void GameManager::handleTradeMoneyForProp(const String& want, const String& give, int reseiverInd) // 2 ednakvi funcs!!!
{
	int idx = getFieldIndByName(give);
	if (idx < 0)
	{
		std::cout << "Incorrect data!";
		return;
	}
	BuildableProperty* prop = static_cast<BuildableProperty*>(board.getFields()[idx]);
	if (prop->getOwner()!=players[currPlayer])
	{
		std::cout << "You can trade only your properties!\n";
		return;
	}
	if (askForConsent(players[reseiverInd]->getUserName()))
	{
		sellAllMorInNeighb(idx);
		prop->setOwner(players[reseiverInd]);
		int sum = strToInt(want);
		players[currPlayer]->addMoney(sum);
	}
}

void GameManager::handleTradePropForMoney(const String& want, const String& give, int reseiverInd)
{
	int idx = getFieldIndByName(want);
	if (idx < 0)
	{
		std::cout << "Incorrect data!";
		return;
	}
	BuildableProperty* prop = static_cast<BuildableProperty*>(board.getFields()[idx]);
	if (prop->getOwner() != players[reseiverInd])
	{
		std::cout << "Incorrect data!";
		return;
	}
	if (askForConsent(players[reseiverInd]->getUserName()))
	{
		sellAllMorInNeighb(idx);
		prop->setOwner(players[currPlayer]);
		int sum = strToInt(give);
		players[reseiverInd]->addMoney(sum);
	}
}

void GameManager::sellAllMorInNeighb(int fieldInd) // separate to func
{
	Vector<BuildableProperty*> neighb;
	collectNeighbour(neighb, fieldInd);
	for (size_t i = 0; i < neighb.getSize(); i++)
	{
		if (neighb[i]->getHasCastle())
		{
			neighb[i]->setHasCastle(false);
			int price = neighb[i]->getCottagePrice() * CASTLE_AS_COTT_CNT;
			neighb[i]->getOwner()->addMoney(price/2);
			castlesLeft++;
		}
		else if (neighb[i]->getCottageCount())
		{
			int cnt = neighb[i]->getCottageCount();
			castlesLeft += cnt;
			neighb[i]->setCottageCoun(0);
			int price = neighb[i]->getCottagePrice() * cnt;
			neighb[i]->getOwner()->addMoney(price / 2);
		}
	}
}

bool GameManager::askForConsent(const String& name)
{
	std::cout << name<< " do you acept the offer? (y/n): ";
	char answer;
	std::cin >> answer;
	return answer == 'y';
}

bool GameManager::canBuildCottage(int fieldInd) const
{
	if (!cottagesLeft)
	{
		std::cout << "There's no cottages left!\n";
		return false;
	}

	if (getFields()[fieldInd]->getType() != FieldType::PROPERTY)
	{
		std::cout << "You can build only on properties!\n";
		return false;
	}

	BuildableProperty* prop = static_cast<BuildableProperty*>(board.getFields()[fieldInd]);

	if (!prop->isBought() || !prop->isOwnedBy(*players[currPlayer]) ||
		prop->getHasCastle() || prop->getCottageCount() == 4 || players[currPlayer]->getBalance() < prop->getCottagePrice())
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

bool GameManager::canBuildCastle(int fieldInd) const
{
	if (!castlesLeft)
	{
		std::cout << "There's no castles left!\n";
		return false;
	}

	if (getFields()[fieldInd]->getType() != FieldType::PROPERTY)
	{
		std::cout << "You can build only on properties!\n";
		return false;
	}

	BuildableProperty* prop = static_cast<BuildableProperty*>(board.getFields()[fieldInd]);

	if (!prop->isBought() ||
		!prop->isOwnedBy(*players[currPlayer]) ||
		prop->getHasCastle() ||
		prop->getCottageCount() != 4 ||  
		players[currPlayer]->getBalance() < prop->getCottagePrice())
		return false;

	Vector<BuildableProperty*> neighb;
	collectNeighbour(neighb, fieldInd);

	if (!ownsWholeSet(neighb)) {
		return false;
	}
	if (!readyForCastle(neighb)) {
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

void GameManager::buildCottage(const String& fieldName)
{
	int fieldInd = getFieldIndByName(fieldName);
	if (fieldInd < 0)
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
	cottagesLeft--;
	players[currPlayer]->giveMoney(prop->getCottagePrice());
	std::cout << "Cottage is build successfully on " << fieldName << "!\n";
}

void GameManager::buildCastle(const String& fieldName)
{
	const int fieldInd = getFieldIndByName(fieldName);
	if (fieldInd < 0) {
		std::cout << "There is no such field!\n";
		return;
	}
	if (!canBuildCastle(fieldInd)) {
		std::cout << "You cannot build a castle on " << fieldName << "!\n";
		return;
	}

	BuildableProperty* prop = static_cast<BuildableProperty*>(board.getFields()[fieldInd]);
	prop->addCastle();                                       
	players[currPlayer]->giveMoney(prop->getCottagePrice()); 

	cottagesLeft += 4;
	--castlesLeft;     

	std::cout << "Castle built successfully on " << fieldName << "!\n";
}

void GameManager::Trade()
{
	String reseiver;
	String want;
	String give;
	std::cout << reseiver << want << give;
	int reseiverInd = getPlayerIndByName(reseiver);
	if (reseiverInd<0)
	{
		std::cout << ""; 
		return;
	}
	if (isNumber(want))
	{
		handleTradeMoneyForProp(want, give, reseiverInd);
	}
	else if (isNumber(give))
	{
		handleTradePropForMoney(want, give, reseiverInd);
	}
	else {
		std::cout << "Incorrect data!\n";
	}
}

bool isNumber(const String& str)
{
	for (size_t i = 0; i < str.getLenght(); i++)
	{
		if (!isDigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

bool isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

int strToInt(const String& str)
{
	int res = 0;
	for (size_t i = 0; i < str.getLenght(); i++)
	{
		int curr = str[i] + '0';
		res = res * 10 + curr;
	}
	return res;
}
