#include "Player.h"
#include "Constants.h"
#include "GameManager.h"
#include "BuildableProperty.h"

Player::Player(String userName) : userName(userName), balance(BEG_BALANCE) {}

Player::Player(String userName, int possition, int balance, bool inJail, int jailTurns, int pairsOfDice) :userName(userName), possition(possition), balance(balance), inJail(inJail), jailTurns(jailTurns), pairsOfDice(pairsOfDice) {}

int Player::getBalance() const
{
    return balance;
}

int Player::getJailTurns() const
{
	return jailTurns;
}

void Player::addJailTurn()
{
	jailTurns++;
}

bool Player::getInJail() const
{
	return inJail;
}

int Player::getPairsOfDice() const
{
	return pairsOfDice;
}

void Player::setPairsOfDice(int val)
{
	pairsOfDice = val;
}

void Player::addPairsOfDice()
{
	pairsOfDice++;
}

bool Player::buyProp(int tax)
{
	if (balance<tax)
	{
		return false;
	}
	else 
	{
		giveMoney(tax);
		return true;
	}
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
	balance -= amount;
}

int Player::getPosition() const
{
	return possition;
}

void Player::changePosition(int change)
{
	possition += change;
	if (possition>=FIELDS_COUNT)
	{
		possition -= FIELDS_COUNT;
	}
}

void Player::goToJail()
{
	inJail = true;
	jailTurns = 0;
}

void Player::getOutOfJail()
{
	inJail = false;
	pairsOfDice = 0;
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

void Player::payForJail()
{
	if (balance>=JAIL_TAX)
	{
		giveMoney(JAIL_TAX);
	}
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
