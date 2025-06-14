#pragma once 
#include "SmallStringOpt.h"
#include "Vector.h"
//#include "Property"

class Player {
	String userName;
	int possition;
	int balance;
	bool inJail;
	int jailTurns=0;
	//Vector< Property*> owned; 
public:
	Player();
	int getBalance() const;
	void buyProp(int tax);
	void collectRent(int rent);
	void payOrGet(int tax);
	int getPosition() const;
	void setPosition(int index);
};