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
	int getBalance() const;
	int getJailTurns() const;
	void addJailTurn(); 
	bool getInJail() const;
	void setInJail(bool currently);	
	int getPairsOfDice() const;
	void setPairsOfDice(int val);
	void addPairsOfDice();
	bool buyProp(int tax);
	void collectRent(int rent);
	void addMoney(int tax);
	void giveMoney(int amount);
	int getPosition() const;
	void changePosition(int change);
	void setPosition(int index);
	void movePosition(int steps);
	String getUserName()const;
	void payForJail();
	bool isBankrupt() const;
	void returnAllProperties();
	void bankrupt();
};