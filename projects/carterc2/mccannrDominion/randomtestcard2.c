/*
 * Random Card Test for the "remodel" card.
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
	int card = remodel;
	int p = 0;
	int cardLimit = 10;
	int r, expectedNumCards, actualNumCards, cardToTrashCost, cardToGainCost;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int numEmptySupplyFails = 0;
	int numPlayedCardCountFails = 0;
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
		G.whoseTurn = p;
		G.deckCount[p] = floor(Random() * cardLimit);
		for (int j = 0; j < G.deckCount[p]; j++) {
			G.deck[p][j] = floor(Random() * great_hall);
		}
		G.discardCount[p] = floor(Random() * MAX_DECK);
		for (int j = 0; j < G.discardCount[p]; j++) {
			G.discard[p][j] = floor(Random() * great_hall);
		}
		G.handCount[p] = floor(Random() * (MAX_HAND - 2)) + 2;
		for (int j = 1; j < G.handCount[p]; j++) {
			G.hand[p][j] = floor(Random() * great_hall);
		}
		G.hand[p][0] = card;
		// Setup choices
		// Card to trash
		choice1 = floor(Random() * (G.handCount[p] - 1)) + 1;
		// Card to gain
		choice2 = floor(Random() * great_hall);
		// Set how many of the card to gain are available
		G.supplyCount[choice2] = floor(Random() * cardLimit);
		
		// Play card
		memcpy(&baseG, &G, sizeof(struct gameState));
		r = cardEffect(card, choice1, choice2, choice3, &G, handPos, &bonus);
		
		// Check that if card costs too much can't get it
		cardToTrashCost = getCost(baseG.hand[p][choice1]);
		cardToGainCost = getCost(choice2);
		if ((cardToTrashCost + 2) > cardToGainCost) {
			if (r != -1) {
				printf("FAIL: Should have returned -1. The chosen card %d, value: %d, costs more card %d, value: %d + 2 = %d.\n", choice2, cardToGainCost, baseG.hand[p][choice1], cardToTrashCost, cardToTrashCost + 2);
				allPass = 0;
			}
		} else if (baseG.supplyCount[choice2] <= 0) {
			if (r != -1) {
				if (numEmptySupplyFails < 1) {
					printf("FAIL: Should have returned -1. The chosen card %d, has a supplyCount of %d so it can not be gained.\n", choice2, baseG.supplyCount[choice2]);
					allPass = 0;
				}
				numEmptySupplyFails++;
			}
		} else {
			// Check for the correct number of cards in hand and discard
			expectedNumCards = baseG.handCount[p] - 2;
			actualNumCards = G.handCount[p];
			if (actualNumCards != expectedNumCards) {
				printf("FAIL: Hand expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
				allPass = 0;
			}
			expectedNumCards = baseG.discardCount[p] + 1;
			actualNumCards = G.discardCount[p];
			if (actualNumCards != expectedNumCards) {
				printf("FAIL: Discard expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
				allPass = 0;
			}
			// Check the playedCardCount
			expectedNumCards = baseG.playedCardCount + 1;
			actualNumCards = G.playedCardCount;
			if (actualNumCards != expectedNumCards) {
				if (numPlayedCardCountFails < 1) {
					printf("FAIL: Played cards expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
					allPass = 0;
				}
				numPlayedCardCountFails++;
			}
		}
	}
	
	if (allPass == 1) {
		printf("TEST SUCCESSFULLY COMPLETED\n");
	} else {
		printf("Number of empty supply failures: %d.\n", numEmptySupplyFails);
		printf("Number of played card count failures: %d.\n", numPlayedCardCountFails);
		printf("TEST FAILED\n");
	}
 }