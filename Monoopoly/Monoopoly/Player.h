#pragma once 
#include "SmallStringOpt.h"
#include "Vector.h"

class Player {
	String userName;
	int possition = 0;
	int balance;
	bool inJail = false;
	int jailTurns=0;

public:
	Player(String userName);
	int getBalance() const;
	void buyProp(int tax);
	void collectRent(int rent);
	void addMoney(int tax);
	void giveMoney(int amount);
	int getPosition() const;
	int changePosition(int change);
	void setPosition(int index);
	void movePosition(int steps);
	String getUserName()const;
	bool isBankrupt() const;
	void returnAllProperties();
	void bankrupt();
};