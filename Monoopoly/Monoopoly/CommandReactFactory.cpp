#include "CommandReactFactory.h"
#include "GameManager.h"

void CommandReactFactory::action(const String& command, bool& rolled, int& dept)
{ //CHECK IF IN  JAIL!!!
	GameManager& gm = GameManager::getInstance();
	if (command == "ROLL")
	{
		if (dept || rolled)
		{
			std::cout << "You cannot roll!\n";
			return;
		}
		gm.rollTheDiesAndMove();
		rolled = true;
		dept = gm.stepOnNewField();
	}
	else if (command == "END")
	{
		if (dept > 0)
		{
			std::cout << "You cannot finish your turn before paying your dept!\n";
			return;
		}
		dept = -1;
	}
	else if (command == "BUY")
	{
		if (!rolled || dept > 0)
		{
			std::cout << "You cannot buy a property right now!\n";
			return;
		}
		gm.buyProperty();
	}
	else if (command == "BUILD")
	{

	}
	else if (command == "SELL")
	{

	}
	else if (command == "TRADE")
	{

	}
	else if (command == "PAYJAIL")
	{

	}
	else if (command == "ASSETS")
	{

	}
	else if (command == "SAVE")
	{

	}
	else if (command == "QUIT")
	{

	}
}
