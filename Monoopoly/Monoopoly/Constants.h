#pragma once

const int MONOPOLY_FIELDS_CNT = 40;
const int GO_PRICE = 200;
const double COTTAGE_FACTOR = 0.15;
const double CASTLE_FACTOR = 0.5;
const int FIELDS_COUNT = 40;
const int GO_AWARD = 200;
const int CARDS_CNT = 6;

int randomNumberGenerator(int size) {
	srand(time(NULL));
	int number = rand() % (size);
	return number;
}//where to put???