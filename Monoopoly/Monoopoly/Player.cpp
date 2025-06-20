#include "Player.h"
#include "Constants.h"

Player::Player()
{
	//TODO
}

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

void Player::addMoney(int tax)
{
	balance += tax;
}

void Player::giveMoney(int amount)
{
	//TODO: do i have enough logic !!!!
	balance -= amount;
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

void Player::movePosition(int steps)
{
	possition += steps;
	if (possition>=FIELDS_COUNT)
	{
		possition -= FIELDS_COUNT;
	}
	else if (possition<0)
	{
		possition += FIELDS_COUNT;
	}
}

String Player::getUserName() const
{
	return userName;
}

bool Player::isBankrupt() const
{
	return balance < 0;
}
