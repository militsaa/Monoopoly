#pragma once
#include "Vector.h"
#include "Player.h"
#include "Board.h"
#include "Property.h"

class GameManager {
	Vector<Player*> players;
	Board& board = Board::getInstance();
	int currPlayer;
	int cottageLeft = 32;
	int castlesLeft = 12;

	GameManager();

	bool canBuild(int fieldInd, Property& prop)const;
	void collectNeighbour(Vector<Property*>& nb,
		int fieldInd);

public:
	GameManager(const GameManager& other) = delete;
	GameManager& operator=(const GameManager& other) = delete;
	static GameManager& getInstance();

	Vector<Player*> getPlayers() const;
	Vector<Field*> getFields() const;
	bool buildCottage(Player& player, int idx);
	void buildCastle();
	//here estimate how many to pay for each prop when on it
};