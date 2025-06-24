#pragma once
#include "SmallStringOpt.h"

class CommandReactFactory
{
public:
	static void action(const String&, bool& rolled, bool& rolledOnce, bool& justGotInPrison, int& dept, bool& onTurn);
};