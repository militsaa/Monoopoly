#include "Player.h"
#include "Constants.h"
#include "GameManager.h"
#include "BuildableProperty.h"

Player::Player(String userName) : userName(userName), balance(BEG_BALANCE) {}

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

int Player::changePosition(int change)
{
	possition += change;
	if (possition>=FIELDS_COUNT)
	{
		possition -= FIELDS_COUNT;
	}
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

void Player::returnAllProperties()
{
	GameManager& gm = GameManager::getInstance();
	for (size_t i = 0; i < FIELDS_COUNT; ++i)
	{
		Field* currField = gm.getFields()[i];

		if (currField->getType() == FieldType::PROPERTY)
		{
			BuildableProperty* currProp = static_cast<BuildableProperty*>(currField);   
			if (currProp->getOwner() == this)    
			{
				currProp->returnProperty();
			}
		}
	}
}

void Player::bankrupt()
{
	returnAllProperties();
	balance = -1;
}
