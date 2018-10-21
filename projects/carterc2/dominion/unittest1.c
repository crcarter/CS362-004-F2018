/*
 * Unit Test for the "scoreFor" function.
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
	int p, r, score, expectedScore;
	int allPass = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	// Check at the start that each player has three points from estates
	p = 0;
	expectedScore = 3;
	score = scoreFor (p, &G);
	if (score == expectedScore) {
		printf("PASS: The score of %d matched the expected score of %d.\n", score, expectedScore);
	} else {
		printf("FAIL: The score of %d did not matched the expected score of %d.\n", score, expectedScore);
		allPass = 0;
	}
	
	if (allPass == 1) {
		printf("TEST SUCCESSFULLY COMPLETED\n");
	} else {
		printf("TEST FAILED\n");
	}
 }