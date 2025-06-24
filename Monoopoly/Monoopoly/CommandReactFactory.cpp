#include "CommandReactFactory.h"
#include "GameManager.h"

void CommandReactFactory::action(const String& command, bool& rolled, bool& rolledOnce, bool& justGotInPrison, int& dept, bool& onTurn)
{
	GameManager& gm = GameManager::getInstance();
	if (command == "ROLL")
	{
		if (!onTurn ||dept || rolled)
		{
			std::cout << "You cannot roll!\n";
			return;
		}
		rolledOnce = true;
		if (gm.rollTheDiesAndMove(rolled))
		{
			justGotInPrison = true;
			return;
		}
		dept = gm.stepOnNewField();
	}
	else if (command == "END")
	{
		if (dept > 0 || !rolled)
		{
			std::cout << "You cannot finish your turn!\n";
			return;
		}
		dept = -1;
	}
	else if (command == "BUY")
	{
		if (!onTurn || !rolledOnce || dept > 0)
		{
			std::cout << "You cannot buy a property right now!\n";
			return;
		}
		gm.buyProperty();
	}
	else if (command == "BUILD")
	{
		if (!onTurn || dept>0)
		{
			std::cout<<"You cannot build!\n";
			return;
		}
		gm.build();
	}
	else if (command == "SELL")
	{
		gm.sell();
	}
	else if (command == "TRADE_FOR_MONEY")
	{
		gm.tradeForMoney();
	}
	else if (command == "TRADE_FOR_PROPERTY")
	{
		gm.tradeForProp();
	}
	else if (command == "PAYJAIL")
	{
		if (!onTurn)
		{
			return;
		}
		gm.payJail();
	}
	else if (command == "SAVE")
	{

	}
	else if (command == "QUIT")
	{
		gm.quit();
		dept = -1;
	}
	else
	{
		std::cout << "Unknown command!\n";
	}
}
