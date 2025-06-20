#pragma once 
#include "Vector.h"
#include "MovePositionCard.h"
#include "PaymentCard.h"
#include "GroupPaymentCard.h"
#include "Constants.h"

class CardDeck {
	Vector<Card*>cards{CARDS_CNT};
	int deckSize = CARDS_CNT;
	void shuffleCards(int times);
public:
	CardDeck();
	~CardDeck();
	Card* draw();
};