#include "Player.h"
#include "Constants.h"

int Player::getBalance() const
{
    return balance;
}

void Player::buyProp(int tax)
{
	balance -= tax;
	//if add vector add in the vector
}

void Player::collectRent(int rent)
{
	balance += rent;
}

void Player::payOrGet(int tax)
{
	//check if its - and if its bigger and then add otions func
	balance += tax;
}

int Player::getPosition() const
{
	return possition;
}

void Player::setPosition(int index)
{
	if (index<MONOPOLY_FIELDS_CNT)
	{
		if (possition>index)
		{
			balance += GO_PRICE;
		}
		possition = index;
	}
}
