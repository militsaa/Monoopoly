#include "GameManager.h"
#include "BuildableProperty.h"
#include "Constants.h"
#include "Random.h"
#include "CommandReactFactory.h"
#include "TaxField.h"
#include "CardField.h"

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

bool GameManager::canSell() const
{
	return false;
}

bool GameManager::canSellCastle(Vector<BuildableProperty*> neighb)
{
	const int baseInd = 0;
	if (cottagesLeft < 4)
	{
		return false;
	}
	for (size_t i = 1; i < neighb.getSize(); i++)
	{
		if (!(neighb[i]->getHasCastle() || neighb[i]->getCottageCount() == 4))
		{
			return false;
		}
	}
	return true;
}

bool GameManager::canSellCottage(Vector<BuildableProperty*> neighb)
{
	const int baseInd = 0;
	if (!neighb[baseInd]->getCottageCount())
	{
		return false;
	}
	for (size_t i = 1; i < neighb.getSize(); i++)
	{
		int difference = neighb[baseInd] - neighb[1] - 1;
		if (difference < -1 || difference>1)
		{
			return false;
		}
	}
	return true;
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
	if (prop->getOwner() != players[currPlayer])
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

void GameManager::sellCastle(BuildableProperty* prop)
{
	prop->sellCastle();
	int price = prop->getCottagePrice() * CASTLE_AS_COTT_CNT;
	prop->getOwner()->addMoney(price / 2);
	castlesLeft++;
}

void GameManager::sellCottages(BuildableProperty* prop, int count)
{
	castlesLeft += count;
	prop->sellCottages(count);
	int price = prop->getCottagePrice() * count;
	prop->getOwner()->addMoney(price / 2);
}

void GameManager::sellAllMorInNeighb(int fieldInd)
{
	Vector<BuildableProperty*> neighb;
	collectNeighbour(neighb, fieldInd);
	for (size_t i = 0; i < neighb.getSize(); i++)
	{
		if (neighb[i]->getHasCastle())
		{
			sellCastle(neighb[i]);
		}
		else if (neighb[i]->getCottageCount())
		{
			int cnt = neighb[i]->getCottageCount();
			sellCottages(neighb[i], cnt);
		}
	}
}

void GameManager::payDeptFromCard(int dept)
{
	players[currPlayer]->giveMoney(dept);
	players[currPlayer]->addMoney(dept);
}

void GameManager::payDept(int dept)
{
	int fieldInd = players[currPlayer]->getPosition();
	Field* field = getFields()[fieldInd];
	if (field->getType() != FieldType::PROPERTY)
	{
		players[currPlayer]->giveMoney(dept);
		return;
	}
	Property* prop = static_cast<Property*>(getFields()[fieldInd]);
	players[currPlayer]->giveMoney(dept);
	prop->getOwner()->addMoney(dept);
}

bool GameManager::askForConsent(const String& name)
{
	std::cout << name << " do you acept the offer? (y/n): ";
	char answer;
	std::cin >> answer;
	return answer == 'y';
}

bool GameManager::rollTheDiesAndMove()
{
	int first = dieGenerator(6);
	int second = dieGenerator(6);
	if (handlePairOfDice(first, second))
	{
		return true;
	}
	std::cout << first << "  " << second;
	players[currPlayer]->changePosition((first + second));
	return false;
}

int GameManager::stepOnNewField(int dept)
{
	int fieldIdx = players[currPlayer]->getPosition();
	Field* field = static_cast<Field*>(getFields()[fieldIdx]);
	if (field->getType() == FieldType::PROPERTY)
	{
		Property* prop = static_cast<Property*>(field);
		return prop->stepedOnProp();
	}
	else if (field->getType() == FieldType::GOTOJAIL)
	{
		players[currPlayer]->setInJail(true);
		players[currPlayer]->setPosition(JAIL_IDX);
	}
	else if(field->getType() == FieldType::TAXFIELD)
	{
		TaxField* taxField = static_cast<TaxField*>(field);
		taxField->applyEffect(*players[currPlayer], dept);
	}
	else if (field->getType() == FieldType::CARDFIELD)
	{
		CardField* taxField = static_cast<CardField*>(field);
		taxField.
	}
}

void GameManager::buyProperty()
{
	int currPoss = players[currPlayer]->getPosition();
	if (getFields()[currPoss]->getType() != FieldType::PROPERTY)
	{
		std::cout << "You can buy only properties!\n";
		return;
	}
	Property* prop = static_cast<Property*>(getFields()[currPoss]);
	prop->buy(*players[currPlayer]);
}

void GameManager::build()
{
	String property;
	String type;
	if (type == "castle")
	{
		buildCottage(property);
	}
	else if (type == "castle")
	{
		buildCastle(property);
	}
}

void GameManager::sell()
{
	String property;
	String type;
	std::cin >> property >> type;
	int idx = getFieldIndByName(property);
	if (idx < 0)
	{
		return;
	}
	else if (board.getFields()[idx]->getType() != FieldType::PROPERTY)
	{
		return;
	}
	Vector<BuildableProperty*> neighb;
	collectNeighbour(neighb, idx);
	if (!ownsWholeSet(neighb))
	{
		return;
	}
	if (type == "castle")
	{
		if (canSellCastle(neighb))
		{
			sellCastle(neighb[0]);
		}
	}
	else if (type == "cottage")
	{
		if (canSellCottage(neighb))
		{
			sellCottages(neighb[0], 1);
		}
	}
	return;
}

void GameManager::quit()
{
	players[currPlayer]->bankrupt();
	removeActivePlayer();
}

void GameManager::setPlayers()
{
	std::cout << "How many players are going to play?";
	int playersCnt = getNumAnswer();
	activePlayers = playersCnt;
	for (size_t i = 0; i < playersCnt; i++)
	{
		std::cout << "Player " << i << " username: ";
		String username;
		std::cin >> username;
		players.push_back(new Player(username));
		clearConsole();
	}
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

Player* GameManager::getCurrPlayer() const
{
	return players[currPlayer];
}

Vector<Field*> GameManager::getFields() const
{
	return board.getFields();
}

void GameManager::removeActivePlayer()
{
	activePlayers--;
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

bool GameManager::handlePairOfDice(int first, int second)
{
	Player* curr = players[currPlayer];
	if (first == second)
	{
		if (curr->getInJail() && curr->getJailTurns() > 0)
		{
			curr->setInJail(false);
		}
		else
		{
			curr->addPairsOfDice();
			return false;
		}
		if (curr->getPairsOfDice() == 3)
		{
			curr->setInJail(true);
			return true;
		}
	}
	else
	{
		if (curr->getInJail())
		{
			curr->addJailTurn();
			return true;
		}
		else
		{
			curr->setPairsOfDice(0);
			return false;
		}
	}
}

bool GameManager::payJail()
{
	if (!players[currPlayer]->getInJail())
	{
		std::cout << "You are not in jail!\n";
	}
	players[currPlayer]->payForJail();
	return players[currPlayer]->getInJail();
}

void GameManager::trade()
{
	String reseiver;
	String want;
	String give;
	std::cout << reseiver << want << give;
	int reseiverInd = getPlayerIndByName(reseiver);
	if (reseiverInd < 0)
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

void GameManager::play()
{
	setPlayers();
	String command;
	bool rolled = false;
	bool justGotInPrison = false;
	int dept = 0;
	bool onTurn = true;

	while (activePlayers>1)
	{
		CommandReactFactory::action(command, rolled, justGotInPrison, dept, onTurn); 
		if (dept > 0)
		{
			if (players[currPlayer]->getBalance() >= dept)
			{
				if (!onTurn)
				{
				payDeptFromCard(dept);
				return;
				}
				payDept(dept);
			}
		}
		if (dept == 0 && !justGotInPrison)
		{
			std::cin >> command;
			clearConsole();
		}
		else
		{
			rolled = false;
			justGotInPrison = false;
			dept = 0;
			currPlayer == players.getSize() - 1 ? currPlayer = 0 : currPlayer++;
			while (players[currPlayer]->isBankrupt())
			{
				currPlayer == players.getSize() - 1 ? currPlayer = 0 : currPlayer++;
			}
		}
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

int getNumAnswer()
{
	String answer;
	std::cin >> answer;
	while (!isNum2to6(answer))
	{
		std::cout << "Please enter a valid symbol! ";
		clearConsole();
		std::cin >> answer;
	}
	clearConsole();
	return strToInt(answer);
}

bool isNum2to6(const String& str)
{
	if (!isNumber(str))
	{
		return false;
	}
	int num = strToInt(str);
	return num >= 2 && num <= 6;
}

void clearConsole()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
