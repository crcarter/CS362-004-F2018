/*
 * Unit Test for the "fullDeckCount" function.
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
	int p, r, count, card, expectedCount;
	int allPass = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, treasure_map};	// Includes adventurer and treasure_map to get the boundaries
    struct gameState G;
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	// Verify game initialized correctly
	if (r != 0) {
		printf("!!!There was an error intiallizing the game.  Test results may be bad.\n");
	}
	
	// Test that at the start of the game the player 0 has 7 coppers
	p = 0;
	card = copper;
	expectedCount = 7;
	count = fullDeckCount(p, card, &G);
	if (count == expectedCount) {
		printf("PASS: The game just started and player %d has %d coppers which is correct.\n", p, count);
	} else {
		printf("FAIL: The game has just started and player %d should have %d coppers, but has %d coppers.\n", p, expectedCount, count);
		allPass = 0;
	}
	
	// Test that at the start of the game the player 0 has 3 estates
	p = 0;
	card = estate;
	expectedCount = 3;
	count = fullDeckCount(p, card, &G);
	if (count == expectedCount) {
		printf("PASS: The game just started and player %d has %d estates which is correct.\n", p, count);
	} else {
		printf("FAIL: The game has just started and player %d should have %d estates, but has %d estatess.\n", p, expectedCount, count);
		allPass = 0;
	}
	
	// Test that at the start of the game the player 1 has 7 coppers
	p = 1;
	card = copper;
	expectedCount = 7;
	count = fullDeckCount(p, card, &G);
	if (count == expectedCount) {
		printf("PASS: The game just started and player %d has %d coppers which is correct.\n", p, count);
	} else {
		printf("FAIL: The game has just started and player %d should have %d coppers, but has %d coppers.\n", p, expectedCount, count);
		allPass = 0;
	}
	
	// Test that at the start of the game the player 1 has 3 estates
	p = 1;
	card = estate;
	expectedCount = 3;
	count = fullDeckCount(p, card, &G);
	if (count == expectedCount) {
		printf("PASS: The game just started and player %d has %d estates which is correct.\n", p, count);
	} else {
		printf("FAIL: The game has just started and player %d should have %d estates, but has %d estatess.\n", p, expectedCount, count);
		allPass = 0;
	}
	
	// Test that at the start of the game player 0 has 0 smithies
	p = 0;
	card = smithy;
	expectedCount = 0;
	count = fullDeckCount(p, card, &G);
	if (count == expectedCount) {
		printf("PASS: The game just started and player %d has %d smithies which is correct.\n", p, count);
	} else {
		printf("FAIL: The game has just started and player %d should have %d smithies, but has %d smithies.\n", p, expectedCount, count);
		allPass = 0;
	}
	
	// Add some cards to the discard pile
	G.discard[0][0] = copper;
	G.discard[0][1] = estate;
	G.discard[0][2] = smithy;
	G.discardCount[0] += 3;
	
	// Test that player 0 has 8 coppers
	p = 0;
	card = copper;
	expectedCount = 8;
	count = fullDeckCount(p, card, &G);
	if (count == expectedCount) {
		printf("PASS: Player %d has %d coppers which is correct.\n", p, count);
	} else {
		printf("FAIL: Player %d should have %d coppers, but has %d coppers.\n", p, expectedCount, count);
		allPass = 0;
	}
	
	// Test that player 0 has 4 estates
	p = 0;
	card = estate;
	expectedCount = 4;
	count = fullDeckCount(p, card, &G);
	if (count == expectedCount) {
		printf("PASS: Player %d has %d estates which is correct.\n", p, count);
	} else {
		printf("FAIL: Player %d should have %d estates, but has %d estatess.\n", p, expectedCount, count);
		allPass = 0;
	}
	
	// Test that player 0 has 1 smithy
	p = 0;
	card = smithy;
	expectedCount = 1;
	count = fullDeckCount(p, card, &G);
	if (count == expectedCount) {
		printf("PASS: Player %d has %d smithies which is correct.\n", p, count);
	} else {
		printf("FAIL: Player %d should have %d smithies, but has %d smithies.\n", p, expectedCount, count);
		allPass = 0;
	}
	
	if (allPass == 1) {
		printf("TEST SUCCESSFULLY COMPLETED\n");
	} else {
		printf("TEST FAILED\n");
	}
 }