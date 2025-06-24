#pragma once
#include "Vector.h"
#include "Player.h"
#include "Board.h"
#include "BuildableProperty.h"

bool isNumber(const String& str);
bool isDigit(char ch);
int strToInt(const String& str);
int getNumAnswer();
bool isNum2to6(const String& str);
void clearConsole();

class GameManager {
	Vector<Player*> players;
	Board& board = Board::getInstance();
	int currPlayer;
	int cottagesLeft = 32;
	int castlesLeft = 12;
	int activePlayers;

	GameManager();

	bool canBuildCottage(int fieldInd)const;
	bool canBuildCastle(int fieldInd)const;
	void collectNeighbour(Vector<BuildableProperty*>& nb, int fieldInd) const;
	bool evenBuildRuleRespected(const Vector<BuildableProperty*>& sameNb) const;
	bool readyForCastle(Vector<BuildableProperty*> neighb) const;
	bool ownsWholeSet(const Vector<BuildableProperty*>& sameNb) const;
	int getFieldIndByName(const String& fieldName)const;
	int getPlayerIndByName(const String& username)const;
	bool canSell()const;
	bool canSellCastle(Vector<BuildableProperty*> neighb) const;
	bool canSellCottage(Vector<BuildableProperty*> neighb);
	void handleTradeMoneyForProp(const String& want, const String& give, int reseiverInd);
	void handleTradePropForMoney(const String& want, const String& give, int reseiverInd);
	void sellCastle(BuildableProperty* prop);
	void sellCottages(BuildableProperty* prop, int count);
	void sellAllMorInNeighb(int fieldInd);
	void payDeptFromCard(int dept);
	void payDept(int dept);
	void buildCottage(const String& fieldName);
	void buildCastle(const String& fieldName);
	bool handlePairOfDice(int first, int second);
	void setPlayers();
	bool askForConsent(const String&);

public:
	GameManager(const GameManager& other) = delete;
	GameManager& operator=(const GameManager& other) = delete;
	static GameManager& getInstance();
	Vector<Player*> getPlayers() const;
	Player* getCurrPlayer() const;
	Vector<Field*> getFields() const;
	void removeActivePlayer();
	bool payJail();
	int getActivePlayerCnt() const;

	void trade();
	bool rollTheDiesAndMove();
	int stepOnNewField(int dept);
	void buyProperty();
	void build();
	void sell();
	void quit();
	void play();
};