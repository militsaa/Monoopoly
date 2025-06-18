#pragma once 
#include "Vector.h"
#include "Field.h"

class Board {
	Vector<Field*> fields;
	// zabrani kopirane i op=!
public:
	Board();
	~Board();
	//Vector<Field*> getFields() const;
	void addCottage(int fieldInd, int playerInd);
};