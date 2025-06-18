#pragma once 
#include "SmallStringOpt.h"
#include "Vector.h"

class Player {
	String userName;
	int possition;
	int balance;
	bool inJail;
	int jailTurns=0;

public:
	Player();
	int getBalance() const;
	void buyProp(int tax);
	void collectRent(int rent);
	void addMoney(int tax);
	void giveMoney(int amount);
	int getPosition() const;
	void setPosition(int index);
};