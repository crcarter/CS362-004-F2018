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
	
	
	
	if (allPass == 1) {
		printf("TEST SUCCESSFULLY COMPLETED\n");
	} else {
		printf("Number of hand count failures: %d.\n", numCountFails);
		printf("Number of hand count with no Adventurer failures: %d.\n", numNoAdventurerCountFails);
		printf("Number of card in hand failures: %d.\n", numWrongCardFails);
		printf("TEST FAILED\n");
	}
 }