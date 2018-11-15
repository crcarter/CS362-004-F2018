/*
 * Random Card Test for the "council_room" card.
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"
 
 int main() {
	 
    int seed = 1000;
	int numTests = 20000;
    int numPlayer = 2;
	int card = council_room;
	int p = 0, otherP = 1;
	int r, expectedNumCards, actualNumCards, expectedNumBuys, actualNumBuys;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int allPass = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, baseG;
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	// Verify game initialized correctly
	if (r != 0) {
		printf("!!!There was an error intiallizing the game.  Test results may be bad.\n");
	}
	
	for (int i = 0; i < numTests; i++) {
		// Setup Gamestate
		p = floor(Random() * 2);
		otherP = (p + 1) % 2;
		G.whoseTurn = p;
		G.deckCount[p] = floor(Random() * MAX_DECK);
		for (int j = 0; j < G.deckCount[p]; j++) {
			G.deck[p][j] = floor(Random() * great_hall);
		}
		G.discardCount[p] = floor(Random() * MAX_DECK);
		for (int j = 0; j < G.discardCount[p]; j++) {
			G.discard[p][j] = floor(Random() * great_hall);
		}
		G.handCount[p] = floor(Random() * (MAX_HAND - 1)) + 1;
		for (int j = 1; j < G.handCount[p]; j++) {
			G.hand[p][j] = floor(Random() * great_hall);
		}
		G.hand[p][0] = card;
		// For the other player
		G.deckCount[otherP] = floor(Random() * MAX_DECK);
		for (int j = 0; j < G.deckCount[otherP]; j++) {
			G.deck[otherP][j] = floor(Random() * great_hall);
		}
		G.discardCount[otherP] = floor(Random() * MAX_DECK);
		for (int j = 0; j < G.discardCount[otherP]; j++) {
			G.discard[otherP][j] = floor(Random() * great_hall);
		}
		G.handCount[otherP] = floor(Random() * (MAX_HAND - 1)) + 1;
		for (int j = 1; j < G.handCount[otherP]; j++) {
			G.hand[otherP][j] = floor(Random() * great_hall);
		}
		
		// Play card
		memcpy(&baseG, &G, sizeof(struct gameState));
		r = cardEffect(card, choice1, choice2, choice3, &G, handPos, &bonus);
		
		// Verify player has +1 buys
		expectedNumBuys = baseG.numBuys + 1;
		actualNumBuys = G.numBuys;
		if (actualNumBuys != expectedNumBuys) {
			printf("FAIL: numBuys expected %d buys, actual %d buys for player %d.\n", expectedNumBuys, actualNumBuys, p);
			allPass = 0;
		}
		
		// Verify hand has 4 more cards and has played the council_room out of the hand
		if ((baseG.deckCount[p] + baseG.discardCount[p]) >= 4) {
			expectedNumCards = baseG.handCount[p] + 4 - 1;
		} else {
			expectedNumCards = baseG.handCount[p] + (baseG.deckCount[p] + baseG.discardCount[p]) - 1;
		}
		actualNumCards = G.handCount[p];
		if (actualNumCards != expectedNumCards) {
			printf("FAIL: Player has the incorrect amount of cards in hand, expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
			allPass = 0;
		}
		
		// Verify the discard and deck have the correct number of cards left
		if ((baseG.deckCount[p] + baseG.discardCount[p]) >= 4) {
			expectedNumCards = (baseG.deckCount[p] + baseG.discardCount[p]) - 4;
		} else {
			expectedNumCards = 0;
		}
		actualNumCards = (G.deckCount[p] + G.discardCount[p]);
		if (actualNumCards != expectedNumCards) {
			printf("FAIL: Player has the incorrect amount of cards in discard and deck, expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
			allPass = 0;
		}
		
		// Verify other players hand has 1 more card
		if ((G.deckCount[otherP] + G.discardCount[otherP]) >= 1) {
			expectedNumCards = baseG.handCount[otherP] + 1;
		} else {
			expectedNumCards = baseG.handCount[otherP];
		}
		actualNumCards = G.handCount[otherP];
		if (actualNumCards != expectedNumCards) {
			printf("FAIL: Player has the incorrect amount of cards in hand, expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, otherP);
			allPass = 0;
		}
		
		// Verify the discard and deck of the other player have the correct number of cards left
		if ((baseG.deckCount[otherP] + baseG.discardCount[otherP]) >= 1) {
			expectedNumCards = (baseG.deckCount[otherP] + baseG.discardCount[otherP]) - 1;
		} else {
			expectedNumCards = 0;
		}
		actualNumCards = (G.deckCount[otherP] + G.discardCount[otherP]);
		if (actualNumCards != expectedNumCards) {
			printf("FAIL: Player has the incorrect amount of cards in discard and deck, expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, otherP);
			allPass = 0;
		}
	}
	
	
	if (allPass == 1) {
		printf("TEST SUCCESSFULLY COMPLETED\n");
	} else {
		printf("TEST FAILED\n");
	}
 }