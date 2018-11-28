/*
 * Unit Test for the "gainCard" function.
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
	int p, r, cardToGet, toFlag, expectedResult, cardGained;
	int numBeforeInSupply, numAfterInSupply;
	char* cardPile;
	int allPass = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, treasure_map};	// Includes adventurer and treasure_map to get the boundaries
    struct gameState G;
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	// Verify game initialized correctly
	if (r != 0) {
		printf("!!!There was an error intiallizing the game.  Test results may be bad.\n");
	}
	
	p = 0;
	cardToGet = duchy;
	expectedResult = 0;
	// Loop to add an estate to the discard, deck, and hand
	for (int i = 0; i < 3; i++) {
		toFlag = i;
		numBeforeInSupply = G.supplyCount[duchy];
		r = gainCard(cardToGet, &G, toFlag, p);
		numAfterInSupply = G.supplyCount[duchy];
		if (toFlag == 0) {
			cardPile = "discard";
			cardGained = G.discard[p][G.discardCount[p] - 1];
		} else if (toFlag == 1) {
			cardPile = "deck";
			cardGained = G.deck[p][G.deckCount[p] - 1];
		} else if (toFlag == 2) {
			cardPile = "hand";
			cardGained = G.hand[p][G.handCount[p] - 1];
		}
		if (r == expectedResult) {
			if (cardGained == cardToGet) {
				if (numBeforeInSupply != numAfterInSupply) {
					printf("PASS: Correctly gained an duchy to %s.\n", cardPile);
				} else {
					printf("FAIL: Correctly gained an duchy to %s, but did not reduce pile in supply.\n", cardPile);
				}
			} else {
				printf("FAIL: It failed to add the card to the %s.\n",cardPile);
				allPass = 0;
			}
		} else {
			printf("FAIL: It returned that there are none left in the pile to gain when there should be.\n");
			allPass = 0;
		}
	}
	
	// Check that you get -1 when the card is not in the supply
	cardToGet = ambassador;
	expectedResult = -1;
	toFlag = 0;
	r = gainCard(cardToGet, &G, toFlag, p);
	if (r == expectedResult) {
		printf("PASS: That card is not in the supply so you could not gain it.\n");
	} else {
		printf("FAIL: You should not have gained that card, it is not in the supply for this game.\n");
		allPass = 0;
	}
	
	// Check that when you get to the end of a pile it doesn't allow you to get any more
	cardToGet = smithy;
	expectedResult = 0;
	toFlag = 0;
	while (G.supplyCount[cardToGet] > 0) {
		r = gainCard(cardToGet, &G, toFlag, p);
		if (r == expectedResult) {
			printf("PASS: The card was gained correctly, %d left in the pile.\n", G.supplyCount[cardToGet]);
		} else {
			printf("FAIL: You should have gained the card.\n");
			allPass = 0;
		}
	}
	expectedResult = -1;
	r = gainCard(cardToGet, &G, toFlag, p);
	if (r == expectedResult) {
		printf("PASS: The card was not gained, the pile in the supply is empty.\n");
	} else {
		printf("FAIL: You should not have gained that card, the supply was empty.\n");
		allPass = 0;
	}
	
	if (allPass == 1) {
		printf("TEST SUCCESSFULLY COMPLETED\n");
	} else {
		printf("TEST FAILED\n");
	}
 }