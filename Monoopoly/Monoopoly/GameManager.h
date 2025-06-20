#pragma once
#include "Vector.h"
#include "Player.h"
#include "Board.h"

class GameManager {
	Vector<Player*> players;
	Board& db = Board::getInstance();
	GameManager();

public:
	GameManager(const GameManager& other) = delete;
	GameManager& operator=(const GameManager& other) = delete;
	static GameManager& getInstance();
	Vector<Player*> getPlayers() const;
	//void buildCottage(int index);
	//void buildCastle(int index);
	//here estimate how many to pay for each prop when on it
};