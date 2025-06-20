#include "CardDeck.h"

void CardDeck::shuffleCards(int times)
{
	int fstRandIndex;
	int secRandIndex;
	for (size_t i = 0; i < times; i++)
	{
		fstRandIndex = randomNumberGenerator(CARDS_CNT);
		secRandIndex = randomNumberGenerator(CARDS_CNT);
		cards.swapVal(fstRandIndex,secRandIndex);
	}
}

CardDeck::CardDeck()
{
	cards.push_back(new MovePositionCard(CardType::MOVE, "Go Back 3 Spaces.", -3));
	cards.push_back(new MovePositionCard(CardType::MOVE, "Advance 5 Spaces.", 5));
	cards.push_back(new PaymentCard(CardType::PAY, "You have won a crossword competition. Collect £100!", 100));
	cards.push_back(new PaymentCard(CardType::PAY, "Speeding fine £15.", -15));
	cards.push_back(new PaymentCard(CardType::GROUP_PAVEMENT, "Grand Opera Opening. Collect $50 from each player", 50));
	cards.push_back(new PaymentCard(CardType::GROUP_PAVEMENT, "You have been elected Chairman of the Board. Pay each player £50", -50));
	shuffleCards(10);
}

CardDeck::~CardDeck()
{
	for (size_t i = 0; i < cards.getSize(); i++)
	{
		delete cards[i];
	}
}

Card* CardDeck::draw()
{
	if (!deckSize)
	{
		deckSize = CARDS_CNT;
		shuffleCards(10);
	}
	deckSize--;
	return cards[deckSize];
}




