#pragma once 
#include "SmallStringOpt.h"
#include "Vector.h"

class Player {
	String userName;
	int possition = 0;
	int balance;
	bool inJail = false;
	int jailTurns=0;
	int pairsOfDice = 0;

public:
	Player(String userName);
	Player(String userName, int possition, int balance, bool inJail, int jailTurns, int pairsOfDice);
	int getBalance() const;
	int getJailTurns() const;
	void addJailTurn(); 
	bool getInJail() const;	
	int getPairsOfDice() const;
	void setPairsOfDice(int val);
	void addPairsOfDice();
	bool buyProp(int tax);
	void collectRent(int rent);
	void addMoney(int tax);
	void giveMoney(int amount);
	int getPosition() const;
	void changePosition(int change);
	void goToJail();
	void getOutOfJail();
	void setPosition(int index);
	void movePosition(int steps);
	String getUserName()const;
	void payForJail();
	bool isBankrupt() const;
	void returnAllProperties();
	void bankrupt();
};