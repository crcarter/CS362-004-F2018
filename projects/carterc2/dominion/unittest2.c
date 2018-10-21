/*
 * Unit Test for the "isGameOver" function.
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
	int r;
	int allPass = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, treasure_map};	// Includes adventurer and treasure_map to get the boundaries
    struct gameState G;
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	// Test that at the start of the game it is not over
	r = isGameOver(&G);
	if (r == 1) {
		printf("FAIL: The game has just started and is over which is wrong.\n");
		allPass = 0;
	} else {
		printf("PASS: The game just started and is not over which is correct.\n");
	}
	
	// Test that the game is over with no provices left
	G.supplyCount[province] = 0;
	r = isGameOver(&G);
	if (r == 1) {
		printf("PASS: The game is over there are no more provinces.\n");
	} else {
		printf("FAIL: The game is not over but should be, there are no more provinces.\n");
		allPass = 0;
	}
	
	// Test that the game is over when estate, smithy, and outpost are all out
	G.supplyCount[province] = 8;	// Reset provinces
	G.supplyCount[estate] = 0;
	G.supplyCount[smithy] = 0;
	G.supplyCount[outpost] = 0;
	r = isGameOver(&G);
	if (r == 1) {
		printf("PASS: The game is over three supply piles are empty.\n");
	} else {
		printf("FAIL: The game is not over but should be, three supply piles are empty.\n");
		allPass = 0;
	}
	
	// Reset the Supply
	G.supplyCount[estate] = 8;
	G.supplyCount[smithy] = 10;
	G.supplyCount[outpost] = 10;
	// Test that the game is over when curse, adventurer, and treasure_map are all out
	G.supplyCount[curse] = 0;
	G.supplyCount[adventurer] = 0;
	G.supplyCount[treasure_map] = 0;
	r = isGameOver(&G);
	if (r == 1) {
		printf("PASS: The game is over three supply piles are empty.\n");
	} else {
		printf("FAIL: The game is not over but should be, three supply piles are empty.\n");
		allPass = 0;
	}
	
	if (allPass == 1) {
		printf("TEST SUCCESSFULLY COMPLETED\n");
	} else {
		printf("TEST FAILED\n");
	}
 }