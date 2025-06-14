#include "Player.h"

int Player::getBalance() const
{
    return balance;
}

void Player::buyProp(int tax)
{
	balance -= tax;
}

void Player::collectRent(int rent)
{
	balance += rent;
}
