#pragma once
#include "Vector.h"
#include "Player.h"
#include "Board.h"

class GameManager {
	Vector<Player*> players;
	Board board;

public:
	GameManager(const Vector<Player*>& initialPlayers);

	void buildCottage(int index);
	void buildCastle(int index);

};