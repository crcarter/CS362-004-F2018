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
	// Verify game initialized correctly
	if (r != 0) {
		printf("!!!There was an error intiallizing the game.  Test results may be bad.\n");
	}
	
	expectedScore = 3;
	// Check at the start that each player has three points from estates
	for (p = 0; p < numPlayer; p++) {
		score = scoreFor (p, &G);
		if (score == expectedScore) {
			printf("PASS: The starting score of %d matched the expected score of %d for player %d.\n", score, expectedScore, p);
		} else {
			printf("FAIL: The starting score of %d did not matched the expected score of %d for player %d.\n", score, expectedScore, p);
			allPass = 0;
		}
	}
	
	// remove all cards from player 0 hand, discard and deck
	p = 0;
	G.handCount[p] = 0;
	G.discardCount[p] = 0;
	G.deckCount[p] = 0;
	
	// Check the correct score of a duchy in the hand
	G.handCount[p] = 1;
	G.hand[p][0] = duchy;
	score = scoreFor (p, &G);
	if (score == expectedScore) {
		printf("PASS: The score of %d matched the expected score of %d for 1 duchy in the players hand.\n", score, expectedScore);
	} else {
		printf("FAIL: The score of %d did not matched the expected score of %d for 1 duchy in the players hand.\n", score, expectedScore);
		allPass = 0;
	}
	
	// Check the correct score of a duchy in the discard
	G.handCount[p] = 0;
	G.discardCount[p] = 1;
	G.discard[p][0] = duchy;
	score = scoreFor (p, &G);
	if (score == expectedScore) {
		printf("PASS: The score of %d matched the expected score of %d for 1 duchy in the players discard.\n", score, expectedScore);
	} else {
		printf("FAIL: The score of %d did not matched the expected score of %d for 1 duchy in the players discard.\n", score, expectedScore);
		allPass = 0;
	}
	
	// Check the correct score of a duchy in the deck
	G.discardCount[p] = 0;
	G.deckCount[p] = 1;
	G.deck[p][0] = duchy;
	score = scoreFor (p, &G);
	if (score == expectedScore) {
		printf("PASS: The score of %d matched the expected score of %d for 1 duchy in the players deck.\n", score, expectedScore);
	} else {
		printf("FAIL: The score of %d did not matched the expected score of %d for 1 duchy in the players deck.\n", score, expectedScore);
		allPass = 0;
	}
	
	// Check the correct score of a gardens
	expectedScore = 2;
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	G.discardCount[p] = 1;
	G.discard[p][0] = gardens;
	// Set hand and deck to all coppers
	for (int i = 0; i < G.handCount[p]; i++) {
		G.hand[p][i] = copper;
	}
	for (int i = 0; i < G.deckCount[p]; i++) {
		G.deck[p][i] = copper;
	}
	score = scoreFor (p, &G);
	if (score == expectedScore) {
		printf("PASS: The score of %d matched the expected score of %d for 1 gardens in the players discard and 11 total cards.\n", score, expectedScore);
	} else {
		printf("FAIL: The score of %d did not matched the expected score of %d for 1 gardens in the players discard and 11 total cards.\n", score, expectedScore);
		allPass = 0;
	}
	
	
	
	if (allPass == 1) {
		printf("TEST SUCCESSFULLY COMPLETED\n");
	} else {
		printf("TEST FAILED\n");
	}
 }