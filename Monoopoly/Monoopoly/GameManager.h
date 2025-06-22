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

	bool canBuild(int fieldInd)const;
	void collectNeighbour(Vector<Property*>& nb,
		int fieldInd) const;
	bool evenBuildRuleRespected(const Vector<Property*>& sameNb) const;
	bool ownsWholeSet(const Vector<Property*>& sameNb) const;
	int getFieldIndByName(String fieldName)const;

public:
	GameManager(const GameManager& other) = delete;
	GameManager& operator=(const GameManager& other) = delete;
	static GameManager& getInstance();

	Vector<Player*> getPlayers() const;
	Vector<Field*> getFields() const;
	void buildCottage(String fieldName);
	void buildCastle();
	//here estimate how many to pay for each prop when on it
};