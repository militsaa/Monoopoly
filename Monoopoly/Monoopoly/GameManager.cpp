#include "GameManager.h"
#include "BuildableProperty.h"
#include "Constants.h"
#include "Random.h"
#include "CommandReactFactory.h"
#include "TaxField.h"
#include "CardField.h"
#include "BoardPrinter.h"
#include <fstream>

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
		if (!(neighb[i]->getCottageCount() == 4 || neighb[i]->getHasCastle()))
		{
			return false;
		}
	}return true;
}

bool GameManager::ownsWholeSet(const Vector<BuildableProperty*>& sameNb) const
{
	for (size_t i = 1; i < sameNb.getSize(); ++i) {
		if (!sameNb[i]->isOwnedBy(players[currPlayer])) {
			std::cout << sameNb[i]->getOwner()->getUserName();
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

bool GameManager::canSellCastle(Vector<BuildableProperty*> neighb) const
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

void GameManager::handleTradeMoneyForProp(int sum, int fieldInd, int reseiverInd)
{
	if (fieldInd < 0 || fieldInd >= getFields().getSize())
	{
		std::cout << "Incorrect data!\n";
		return;
	}
	Field* field = static_cast<Field*>(board.getFields()[fieldInd]);
	if (field->getType() != FieldType::PROPERTY)
	{
		std::cout << "You can trade only propertirs!\n";
		return;
	}
	BuildableProperty* prop = static_cast<BuildableProperty*>(board.getFields()[fieldInd]);
	if (prop->getOwner() != players[reseiverInd])
	{
		std::cout << "You can trade only your properties!\n";
		return;
	}
	if (players[currPlayer]->getBalance() < sum)
	{
		std::cout << "You don't have enough money to trade!\n";
		return;
	}
	if (askForConsent(players[reseiverInd]->getUserName()))
	{
		sellAllMorInNeighb(fieldInd);
		prop->setOwner(players[currPlayer]);
		players[currPlayer]->giveMoney(sum);
		players[reseiverInd]->addMoney(sum);
	}
}

void GameManager::handleTradePropForMoney(int fieldInd, int sum, int reseiverInd)
{
	if (fieldInd < 0)
	{
		std::cout << "Incorrect data!";
		return;
	}
	BuildableProperty* prop = static_cast<BuildableProperty*>(board.getFields()[fieldInd]);
	if (prop->getOwner() != players[currPlayer])
	{
		std::cout << "Incorrect data!";
		return;
	}
	if (players[reseiverInd]->getBalance() < sum)
	{
		std::cout << players[reseiverInd]->getUserName() << " doesn't have enough money to trade!\n";
		return;
	}
	if (askForConsent(players[reseiverInd]->getUserName()))
	{
		sellAllMorInNeighb(fieldInd);
		prop->setOwner(players[reseiverInd]);
		players[reseiverInd]->giveMoney(sum);
		players[currPlayer]->addMoney(sum);
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

void GameManager::endTheGame() const
{
	Player* left = players[0];
	for (size_t i = 1; i < players.getSize(); i++)
	{
		if (!players[i]->isBankrupt())
		{
			left = players[i];
		}
	}
	std::cout << "Congratilation " << left->getUserName() << " you won the game!";
}

void GameManager::savePlayers()
{
	std::ofstream os("players.txt", std::ios::binary | std::ios::trunc);
	if (!os.is_open())
	{
		std::cout << "failed" << '/n';
		return;
	}
	for (size_t i = 0; i < players.getSize(); i++) {
		if (players[i]->isBankrupt())
		{
			continue;
		}
		String userName = players[i]->getUserName();
		size_t len = userName.getSize();
		os.write((const char*)&len, sizeof(size_t));
		os.write(userName.c_str(), len);
		int poss = players[i]->getPosition();
		os.write((const char*)&poss, sizeof(int));
		int balance = players[i]->getBalance();
		os.write((const char*)&balance, sizeof(int));
		bool inJail = players[i]->getInJail();
		os.write((const char*)&balance, sizeof(bool));
		int jailTurns = players[i]->getJailTurns();
		os.write((const char*)&jailTurns, sizeof(int));
		int pairs = players[i]->getPairsOfDice();
		os.write((const char*)&pairs, sizeof(int));
	}
	os.close();
}

void GameManager::saveFields()
{
	std::ofstream os("fields.txt", std::ios::binary | std::ios::trunc);
	if (!os.is_open())
	{
		std::cout << "failed" << '/n';
		return;
	}
	Field* field;
	for (int i = 0; i < getFields().getSize(); i++)
	{
		field = getFields()[i];
		int index;
		if (field->getType() == FieldType::PROPERTY)
		{
			Property* prop = static_cast<Property*>(field);
			if (prop->isBought())
			{
				Player* owner = prop->getOwner();
				index = getIndexOfPlayer(owner);
				if (index >= 0)
				{
					os.write((const char*)&i, sizeof(int));
					os.write((const char*)&index, sizeof(int));
				}
			}
		}
	}
	os.close();
}

bool GameManager::loadPlayers()
{
	std::ifstream is("players.txt", std::ios::binary);
	if (!is.is_open()) {
		return false;
	}
	int userNameLen =0;
	String userName;
	int poss=0;
	int balance=0;
	bool inJail=false;
	int jailTurns = 0;
	int pairs=0;
	while (is.peek() != EOF) {
		is.read((char*)&userNameLen, sizeof(int));
		readStringFromFile(is, userName);
		is.read((char*)&poss, sizeof(int));
		is.read((char*)&balance, sizeof(int));
		is.read((char*)&inJail, sizeof(bool));
		is.read((char*)&jailTurns, sizeof(int));
		is.read((char*)&pairs, sizeof(int));
		players.push_back(new Player(userName, poss, balance, inJail, jailTurns, pairs));
	}
	return true;
}

bool GameManager::loadFields()
{
	std::ifstream is("fields.txt", std::ios::binary);
	if (!is.is_open()) {
		return false;
	}
	int fieldIndex;
	int playerIndex;
	Property* prop;
	while (is.peek() != EOF) {
		is.read((char*)&fieldIndex, sizeof(int));
		is.read((char*)&playerIndex, sizeof(int));
		prop = static_cast <Property*>(getFields()[fieldIndex]);
		prop->setOwner(players[playerIndex]);
	}
	return true;
}

void GameManager::readStringFromFile(std::istream& is, String& curr)
{
	size_t len;
	is.read((char*)&len, sizeof(size_t));
	char* buff = new char[len + 1];
	is.read(buff, len);
	buff[len] = '\0';
	curr = buff;
	delete[] buff;
}

int GameManager::getIndexOfPlayer(Player* p)
{
	for (size_t i = 0; i < players.getSize(); i++)
	{
		if (players[i] == p)
		{
			return i;
		}
	}
	return -1;
}

//void GameManager::presentBoard(const Vector<Field*>& fields, int width) const
//{
//	printBoard(fields, width);
//}

bool GameManager::rollTheDiesAndMove(bool& rolled)
{
	int first = dieGenerator(6);
	int second = dieGenerator(6);
	if (handlePairOfDice(first, second, rolled))
	{
		return true;
	}
	std::cout << first << "  " << second << '\n';
	players[currPlayer]->changePosition((first + second));
	return false;
}

int GameManager::stepOnNewField()
{
	int fieldIdx = players[currPlayer]->getPosition();
	Field* field = static_cast<Field*>(getFields()[fieldIdx]);
	if (field->getType() == FieldType::PROPERTY)
	{
		Property* prop = static_cast<Property*>(field);
		std::cout << "You stept on " << prop->getName() << " !\n";
		return prop->stepedOnProp();
	}
	else if (field->getType() == FieldType::GOTOJAIL)
	{
		players[currPlayer]->goToJail();
		std::cout << field->getName() << " !\n";
		players[currPlayer]->setPosition(JAIL_IDX);
	}
	else if (field->getType() == FieldType::TAXFIELD)
	{
		TaxField* taxField = static_cast<TaxField*>(field);
		std::cout << taxField->getName() << " " << taxField->getDescription() << "\n";
		taxField->applyEffect(*players[currPlayer]);
	}
	else if (field->getType() == FieldType::CARDFIELD)
	{
		CardField* cardField = static_cast<CardField*>(field);
		cardField->drawAndApply(*players[currPlayer]);
		if (players[currPlayer]->isBankrupt())
		{
			return -1;
		}
	}
	else
	{
		std::cout << "Steped on " << field->getName() << '\n';
	}
	return 0;
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
	String type;
	int idx;
	std::cin >> type >> idx;
	if (type == "COTTAGE")
	{
		buildCottage(idx);
	}
	else if (type == "CASTLE")
	{
		buildCastle(idx);
	}
	else
	{
		std::cout << "Incorrect data!\n";
	}
}

void GameManager::sell()
{
	String type;
	int idx;
	std::cin >> type >> idx;
	if (idx < 0 || idx >= FIELDS_COUNT)
	{
		std::cout << "There is no such field!\n";
		return;
	}
	else if (board.getFields()[idx]->getType() != FieldType::PROPERTY)
	{
		std::cout << "This is not property field!\n";
		return;
	}
	Vector<BuildableProperty*> neighb;
	collectNeighbour(neighb, idx);
	if (!ownsWholeSet(neighb))
	{
		return;
	}
	if (type == "CASTLE")
	{
		if (canSellCastle(neighb))
		{
			sellCastle(neighb[0]);
			std::cout << "Castle sold successfully!\n";
			return;
		}
		std::cout << "Cannot sell the castle!\n";
	}
	else if (type == "COTTAGE")
	{
		if (canSellCottage(neighb))
		{
			sellCottages(neighb[0], 1);
			std::cout << "Cottage sold successfully!\n";
			return;
		}
		std::cout << "Cannot sell the cottage!\n";
	}
	else
	{
		std::cout << "Incorrect data!\n";
	}
	return;
}

void GameManager::quit()
{
	players[currPlayer]->bankrupt();
	removeActivePlayer();
	std::cout << players[currPlayer]->getUserName() << " quitted the game!\n";
}

void GameManager::saveGame()
{
	savePlayers();
	saveFields();
	return;
}

void GameManager::setPlayers()
{
	if ((!isBinaryFileEmpty("players.txt") && !isBinaryFileEmpty("fields.txt")))
	{
		std::cout << "Would you like to continue the game ";
		if (getNumAnswer())
		{
			if (loadPlayers()||loadFields())
			{
				return;
			}
			std::cout << "failed!\n";
		} 
	}
	std::cout << "How many players are going to play? (2-6): ";
	int playersCnt = getNumAnswer();
	activePlayers = playersCnt;
	for (size_t i = 0; i < playersCnt; i++)
	{
		std::cout << "Player " << i + 1 << " username: ";
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

	if (!prop->isBought() || !prop->isOwnedBy(players[currPlayer]) ||
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
		!prop->isOwnedBy(players[currPlayer]) ||
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

void GameManager::buildCottage(int fieldIdx)
{
	if (fieldIdx < 0 || fieldIdx >= FIELDS_COUNT)
	{
		std::cout << "There is no such field!\n";
		return;
	}
	if (!canBuildCottage(fieldIdx))
	{
		std::cout << "You cannot build a cottage there!\n";
		return;
	}
	BuildableProperty* prop = static_cast<BuildableProperty*>(board.getFields()[fieldIdx]);
	prop->addCottage();
	cottagesLeft--;
	players[currPlayer]->giveMoney(prop->getCottagePrice());
	std::cout << "Cottage is build successfully on " << getFields()[fieldIdx]->getName() << "!\n";
}

void GameManager::buildCastle(int fieldIdx)
{
	if (fieldIdx < 0 || fieldIdx >= FIELDS_COUNT)
	{
		std::cout << "There is no such field!\n";
		return;
	}
	if (!canBuildCastle(fieldIdx))
	{
		std::cout << "You cannot build a castle there!\n";
		return;
	}

	BuildableProperty* prop = static_cast<BuildableProperty*>(board.getFields()[fieldIdx]);
	prop->addCastle();
	players[currPlayer]->giveMoney(prop->getCottagePrice());

	cottagesLeft += 4;
	--castlesLeft;

	std::cout << "Castle built successfully on " << getFields()[fieldIdx]->getName() << "!\n";
}

bool GameManager::handlePairOfDice(int first, int second, bool& rolled)
{
	Player* curr = players[currPlayer];
	if (first == second)
	{
		rolled = false;
		if (curr->getInJail() && curr->getJailTurns() > 0)
		{
			curr->getOutOfJail();
			return false;
		}
		else
		{
			curr->addPairsOfDice();
			if (curr->getPairsOfDice() == 3)
			{
				curr->goToJail();
				std::cout << "Third pair! Go to jail!\n";
				return true;
			}
			return false;
		}
	}
	else
	{
		rolled = true;
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

int GameManager::getActivePlayerCnt() const
{
	return activePlayers;
}

void GameManager::tradeForProp()
{
	int money = 0;
	int fieldInd = 0;
	String reseiver;
	std::cin >> money >> fieldInd >> reseiver;
	int reseiverInd = getPlayerIndByName(reseiver);
	if (reseiverInd < 0)
	{
		std::cout << "";
		return;
	}
	handleTradeMoneyForProp(money, fieldInd, reseiverInd);
}

void GameManager::tradeForMoney()
{
	int fieldInd = 0;
	int money = 0;
	String reseiver;
	std::cin >> money >> fieldInd >> reseiver;
	int reseiverInd = getPlayerIndByName(reseiver);
	if (reseiverInd < 0)
	{
		std::cout << "";
		return;
	}
	handleTradePropForMoney(fieldInd, money, reseiverInd);
}

void GameManager::play()
{
	//presentBoard(getFields(), 12);
	setPlayers();
	String command;
	bool rolled = false;
	bool rolledOnce = false;
	bool justGotInPrison = false;
	int dept = 0;
	bool onTurn = true;

	while (activePlayers > 1)
	{

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
				dept = 0;
			}
		}
		if (dept == 0 && !justGotInPrison)
		{
			std::cout << players[currPlayer]->getUserName() << "(b:" << players[currPlayer]->getBalance() << ") :";
			std::cin >> command;
		}
		else
		{
			rolled = false;
			rolledOnce = false;
			justGotInPrison = false;
			dept = 0;
			currPlayer == players.getSize() - 1 ? currPlayer = 0 : currPlayer++;
			while (players[currPlayer]->isBankrupt())
			{
				currPlayer == players.getSize() - 1 ? currPlayer = 0 : currPlayer++;
			}
			std::cout << players[currPlayer]->getUserName() << "(b:" << players[currPlayer]->getBalance() << ") :";
			std::cin >> command;
		}
		CommandReactFactory::action(command, rolled, rolledOnce, justGotInPrison, dept, onTurn);
		clearConsole();
	}
	void endTheGame();
}
 bool isBinaryFileEmpty(const char* filename)
{
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		return true;
	}
	return file.tellg() == 0;
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
		int curr = str[i] - '0';
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

bool getCorrectAnswer()
{
	char answer;
	std::cin >> answer;
	while (!(answer == 'y' || answer == 'Y' || answer == 'n' || answer == 'N'))
	{
		std::cout << "Please enter a valid symbol! ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> answer;
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return answer == 'y';
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
