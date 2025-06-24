#pragma once
#include "SmallStringOpt.h"

class CommandReactFactory
{
public:
	static void action(const String&, bool& rolled, bool& justGotInPrison, int& dept);
};