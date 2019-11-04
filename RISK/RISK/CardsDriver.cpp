#include "Cards.h"
#include <iostream>

void CardDriver::run()
{
	int a = 53;
	Deck testDeck(a);

	testDeck.displayCardsDistribution();

	Hand h1(testDeck);

	for (int t{ 1 }; t <= 15; ++t) {
		h1.draw();
	}

	h1.printCards();

	while (h1.hasExchange()) {
		h1.exchange();
	}

}