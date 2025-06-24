#include "CommandReactFactory.h"
#include "GameManager.h"

void CommandReactFactory::action(const String& command, bool& rolled, bool& justGotInPrison, int& dept, bool& onTurn)
{
	GameManager& gm = GameManager::getInstance();
	if (command == "ROLL")
	{
		if (!onTurn)
		{
			std::cout << "Its not your turn!\n";
			return;
		}
		if (dept || rolled)
		{
			std::cout << "You cannot roll!\n";
			return;
		}
		if (gm.rollTheDiesAndMove())
		{
			justGotInPrison = true;
			return;
		}
		rolled = true;
		dept = gm.stepOnNewField(dept);
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
		if (!onTurn)
		{
			return;
		}
		if (!rolled || dept > 0)
		{
			std::cout << "You cannot buy a property right now!\n";
			return;
		}
		gm.buyProperty();
	}
	else if (command == "BUILD")
	{
		if (!onTurn)
		{
			return;
		}
		gm.build();
	}
	else if (command == "SELL")
	{
		gm.sell();
	}
	else if (command == "TRADE")
	{
		gm.trade();
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
}
