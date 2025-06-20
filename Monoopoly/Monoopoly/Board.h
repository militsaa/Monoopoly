#pragma once 
#include "Vector.h"
#include "Field.h"

class Board {
	Vector<Field*> fields;
	Board();

public:
	~Board();
	Board(const Board& other) = delete;
	Board& operator=(const Board& other) = delete;
	static Board& getInstance();
	Vector<Field*> getFields()const;
};