/*
 * Random Card Test for the "adventurer" card.
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
	int card = adventurer;
	int p = 0;
	int supplyPass = 1;
	int numTreasureCards = 0;
	int r, expectedNumCards, actualNumCards, cardDrawn, expectedNumActions, actualNumActions;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int numCountFails = 0;
	int numNoAdventurerCountFails = 0;
	int numWrongCardFails = 0;
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
		numTreasureCards = 0;
		p = floor(Random() * 2);
		G.whoseTurn = p;
		G.deckCount[p] = floor(Random() * MAX_DECK);
		for (int j = 0; j < G.deckCount[p]; j++) {
			G.deck[p][j] = floor(Random() * great_hall);
			if (G.deck[p][j] == copper || G.deck[p][j] == silver || G.deck[p][j] == gold) {
				numTreasureCards++;
			}
		}
		G.discardCount[p] = floor(Random() * MAX_DECK);
		for (int j = 0; j < G.discardCount[p]; j++) {
			G.discard[p][j] = floor(Random() * great_hall);
			if (G.discard[p][j] == copper || G.discard[p][j] == silver || G.discard[p][j] == gold) {
				numTreasureCards++;
			}
		}
		G.handCount[p] = floor(Random() * (MAX_HAND - 1 - 2)) + 1;
		for (int j = 1; j < G.handCount[p]; j++) {
			G.hand[p][j] = floor(Random() * great_hall);
		}
		G.hand[p][0] = card;
		
		// Play card
		memcpy(&baseG, &G, sizeof(struct gameState));
		r = cardEffect(card, choice1, choice2, choice3, &G, handPos, &bonus);
		
		// Check the results
		// Verify hand has 2 more cards and has played the adventurer out of the hand
		if (numTreasureCards >= 2) {
			expectedNumCards = baseG.handCount[p] + 2 - 1;
		} else {
			expectedNumCards = baseG.handCount[p] + numTreasureCards - 1;
		}
		actualNumCards = G.handCount[p];
		if (actualNumCards == expectedNumCards) {
			//printf("PASS: The cards were gained correctly and 1 played from the hand, expected %d cards, actual %d cards.\n", expectedNumCards, actualNumCards);
		} else {
			if (numCountFails <= 0) {
				printf("FAIL: Player %d, has the incorrect amount of cards in hand, expected %d cards, actual %d cards, numTreasureCards: %d.\n", p, expectedNumCards, actualNumCards, numTreasureCards);
				allPass = 0;
			}
			numCountFails++;
		}
		// knowing Adveturer doesn't leave the hand check that it has the correct number of gained cards.
		if (numTreasureCards >= 2) {
			expectedNumCards = baseG.handCount[p] + 2;
		} else {
			expectedNumCards = baseG.handCount[p] + numTreasureCards;
		}
		actualNumCards = G.handCount[p];
		if (actualNumCards == expectedNumCards) {
			//printf("PASS: The cards were gained correctly and 1 played from the hand, expected %d cards, actual %d cards.\n", expectedNumCards, actualNumCards);
		} else {
			//if (numNoAdventurerCountFails <= 0) {
				printf("FAIL: Player %d, has the incorrect amount of cards in hand, not counting Adventurer, expected %d cards, actual %d cards, numTreasureCards: %d.\n", p, expectedNumCards, actualNumCards, numTreasureCards);
				allPass = 0;
			//}
			numNoAdventurerCountFails++;
		}
		
		// Verify the last two cards are treasure cards
		if (numTreasureCards >= 1) {
			cardDrawn = G.hand[p][G.handCount[p]-1];
			if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
				//printf("PASS: The last card is %d which is a treasure.\n", cardDrawn);
			} else {
				printf("FAIL: Player %d, the last card is %d which is not a treasure. numTreasureCards: %d.\n", p, cardDrawn, numTreasureCards);
				allPass = 0;
				numWrongCardFails++;
			}
		}
		if (numTreasureCards >= 2) {
			cardDrawn = G.hand[p][G.handCount[p]-2];
			if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
				//printf("PASS: The second to last card is %d which is a treasure.\n", cardDrawn);
			} else {
				printf("FAIL: Player %d, the second to last card is %d which is not a treasure. numTreasureCards: %d.\n", p, cardDrawn, numTreasureCards);
				allPass = 0;
				numWrongCardFails++;
			}
		}
	}
	
	
	if (allPass == 1) {
		printf("TEST SUCCESSFULLY COMPLETED\n");
	} else {
		printf("Number of hand count failures: %d.\n", numCountFails);
		printf("Number of hand count with no Adventurer failures: %d.\n", numNoAdventurerCountFails);
		printf("Number of card in hand failures: %d.\n", numWrongCardFails);
		printf("TEST FAILED\n");
	}
 }