/*
 * Card Test for the "smithy" card.
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
 
 int main() {
	 
    int seed = 1000;
    int numPlayer = 2;
	int card = smithy;
	int p = 0;
	int supplyPass = 1;
	int r, expectedNumCards, actualNumCards, expectedNumActions, actualNumActions;
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
	
	G.hand[p][handPos] = smithy;
	// copy the game state to a base case
	memcpy(&baseG, &G, sizeof(struct gameState));
	r = cardEffect(card, choice1, choice2, choice3, &G, handPos, &bonus);
	
	// Verify that card is no longer in hand
	if (G.hand[p][handPos] != card) {
		printf("PASS: %d was played, and handPos is now %d.\n", card, G.hand[p][handPos]);
	} else {
		printf("FAIL: %d was played, and handPos is still %d.\n", card, G.hand[p][handPos]);
		allPass = 0;
	}
	
	// Verify hand has 3 more cards and has played the smithy out of the hand
	expectedNumCards = baseG.handCount[p] + 3 - 1;
	actualNumCards = G.handCount[p];
	if (actualNumCards == expectedNumCards) {
		printf("PASS: The 3 cards was gained correctly and 1 played from the hand, expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Player has the incorrect amount of cards in hand, expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	
	// Verify deck has 3 less cards
	expectedNumCards = baseG.deckCount[p] - 3;
	actualNumCards = G.deckCount[p];
	if (actualNumCards == expectedNumCards) {
		printf("PASS: Deck expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Deck expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	
	// Verify discard did not change
	expectedNumCards = baseG.discardCount[p];
	actualNumCards = G.discardCount[p];
	if (actualNumCards == expectedNumCards && memcmp(G.discard, baseG.discard, sizeof(int) * actualNumCards) == 0) {
		printf("PASS: Discard expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Discard expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	
	// Verify player has same numActions
	expectedNumActions = baseG.numActions;
	actualNumActions = G.numActions;
	if (actualNumActions == expectedNumActions) {
		printf("PASS: numActions expected %d action, actual %d actions for player %d.\n", expectedNumActions, actualNumActions, p);
	} else {
		printf("FAIL: numActions expected %d actions, actual %d actions for player %d.\n", expectedNumActions, actualNumActions, p);
		allPass = 0;
	}
	
	//Verify supply has not changed
	for (int i = 0; i <= treasure_map; i++) {
		expectedNumCards = baseG.supplyCount[i];
		actualNumCards = G.supplyCount[i];
		if (actualNumCards != expectedNumCards) {
			printf("FAIL: Pile %d, expected %d cards, actual %d cards.\n", i, expectedNumCards, actualNumCards);
			allPass = 0;
			supplyPass = 0;
		}
	}
	if (supplyPass == 1) {
		printf("PASS: All supply piles matched.\n");
	}
	
	// Verify that the other players deck did not change
	p = 1;
	expectedNumCards = baseG.deckCount[p];
	actualNumCards = G.deckCount[p];
	if (actualNumCards == expectedNumCards && memcmp(G.deck, baseG.deck, sizeof(int) * actualNumCards) == 0) {
		printf("PASS: Deck expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Deck expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	expectedNumCards = baseG.handCount[p];
	actualNumCards = G.handCount[p];
	if (actualNumCards == expectedNumCards && memcmp(G.hand, baseG.hand, sizeof(int) * actualNumCards) == 0) {
		printf("PASS: Hand expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Hand expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	expectedNumCards = baseG.discardCount[p];
	actualNumCards = G.discardCount[p];
	if (actualNumCards == expectedNumCards && memcmp(G.discard, baseG.discard, sizeof(int) * actualNumCards) == 0) {
		printf("PASS: Discard expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Discard expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	
	if (allPass == 1) {
		printf("TEST SUCCESSFULLY COMPLETED\n");
	} else {
		printf("TEST FAILED\n");
	}
 }