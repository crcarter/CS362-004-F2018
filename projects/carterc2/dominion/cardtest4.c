/*
 * Card Test for the "baron" card.
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
	int card = baron;
	int p = 0;
	int supplyPass = 1;
	int r, expectedNumCards, actualNumCards, expectedNumBuys, actualNumBuys, expectedNumCoins, actualNumCoins, expectedNumActions, actualNumActions;
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
	
	// Choice1 to not discard Estate
	printf("---Checking choice to not discard estate.---\n");
	G.hand[p][handPos] = card;
	choice1 = 0;
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
	
	// Verify hand has 0 more card and has played the baron out of the hand
	expectedNumCards = baseG.handCount[p] - 1;
	actualNumCards = G.handCount[p];
	if (actualNumCards == expectedNumCards) {
		printf("PASS: 1 card played from the hand, expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Player has the incorrect amount of cards in hand, expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	
	// Verify deck has same number of cards
	expectedNumCards = baseG.deckCount[p];
	actualNumCards = G.deckCount[p];
	if (actualNumCards == expectedNumCards && memcmp(G.deck, baseG.deck, sizeof(int) * actualNumCards) == 0) {
		printf("PASS: Deck expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Deck expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	
	// Verify discard gained 1 estate
	expectedNumCards = baseG.discardCount[p] + 1;
	actualNumCards = G.discardCount[p];
	if (actualNumCards == expectedNumCards && G.discard[p][0] == estate) {
		printf("PASS: Discard expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Discard expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	
	// Verify player has +1 buys
	expectedNumBuys = baseG.numBuys + 1;
	actualNumBuys = G.numBuys;
	if (actualNumBuys == expectedNumBuys) {
		printf("PASS: numBuys expected %d buys, actual %d buys for player %d.\n", expectedNumBuys, actualNumBuys, p);
	} else {
		printf("FAIL: numBuys expected %d buys, actual %d buys for player %d.\n", expectedNumBuys, actualNumBuys, p);
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
	
	// Verify one estate was removed from supply
	expectedNumCards = baseG.supplyCount[estate];
	actualNumCards = G.supplyCount[estate];
	if (actualNumCards == expectedNumCards) {
		printf("PASS: Pile %d, expected %d cards, actual %d cards.\n", estate, expectedNumCards, actualNumCards);
	} else {
		printf("FAIL: Pile %d, expected %d cards, actual %d cards.\n", estate, expectedNumCards, actualNumCards);
		allPass = 0;
	}
	
	// Choice1 to discard Estate, no estate in hand----------------
	// Reset game
	printf("---Checking choice to discard estate without estate in hand.---\n");
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	// Verify game initialized correctly
	if (r != 0) {
		printf("!!!There was an error intiallizing the game.  Test results may be bad.\n");
	}
	G.hand[p][handPos] = card;
	choice1 = 1;
	G.hand[p][handPos+1] = copper;
	G.hand[p][handPos+2] = copper;
	G.hand[p][handPos+3] = copper;
	G.hand[p][handPos+4] = copper;
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
	
	// Verify hand has played the baron out of the hand
	expectedNumCards = baseG.handCount[p] - 1;
	actualNumCards = G.handCount[p];
	if (actualNumCards == expectedNumCards) {
		printf("PASS: 1 card played from the hand and 1 discarded, expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Player has the incorrect amount of cards in hand, expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	
	// Verify deck has same number of cards
	expectedNumCards = baseG.deckCount[p];
	actualNumCards = G.deckCount[p];
	if (actualNumCards == expectedNumCards && memcmp(G.deck, baseG.deck, sizeof(int) * actualNumCards) == 0) {
		printf("PASS: Deck expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Deck expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	
	// Verify discard gained 1 estate
	expectedNumCards = baseG.discardCount[p] + 1;
	actualNumCards = G.discardCount[p];
	if (actualNumCards == expectedNumCards && G.discard[p][0] == estate) {
		printf("PASS: Discard expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Discard expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	
	// Choice1 to discard Estate----------------
	// Reset game
	printf("---Checking choice to discard estate with estate in hand.---\n");
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	// Verify game initialized correctly
	if (r != 0) {
		printf("!!!There was an error intiallizing the game.  Test results may be bad.\n");
	}
	G.hand[p][handPos] = card;
	choice1 = 1;
	G.hand[p][handPos+1] = estate;
	G.hand[p][handPos+2] = copper;
	G.hand[p][handPos+3] = copper;
	G.hand[p][handPos+4] = copper;
	G.hand[p][handPos+5] = smithy;
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
	
	// Verify that estate gets replaced with the correct card
	if (G.hand[p][handPos+1] != estate) {
		printf("PASS: %d was discarded, and handPos is now %d.\n", estate, G.hand[p][handPos+1]);
	} else {
		printf("FAIL: %d was discarded, and handPos is still %d.\n", estate, G.hand[p][handPos+1]);
		allPass = 0;
	}
	
	// Verify hand has 1 less card and has played the baron out of the hand
	expectedNumCards = baseG.handCount[p] - 1 - 1;
	actualNumCards = G.handCount[p];
	if (actualNumCards == expectedNumCards) {
		printf("PASS: 1 card played from the hand and 1 discarded, expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Player has the incorrect amount of cards in hand, expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	
	// Verify deck has same number of cards
	expectedNumCards = baseG.deckCount[p];
	actualNumCards = G.deckCount[p];
	if (actualNumCards == expectedNumCards && memcmp(G.deck, baseG.deck, sizeof(int) * actualNumCards) == 0) {
		printf("PASS: Deck expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Deck expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	
	// Verify discard gained 1 estate
	expectedNumCards = baseG.discardCount[p] + 1;
	actualNumCards = G.discardCount[p];
	if (actualNumCards == expectedNumCards && G.discard[p][0] == estate) {
		printf("PASS: Discard expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
	} else {
		printf("FAIL: Discard expected %d cards, actual %d cards for player %d.\n", expectedNumCards, actualNumCards, p);
		allPass = 0;
	}
	
	// Verify player has +1 buys
	expectedNumBuys = baseG.numBuys + 1;
	actualNumBuys = G.numBuys;
	if (actualNumBuys == expectedNumBuys) {
		printf("PASS: numBuys expected %d buys, actual %d buys for player %d.\n", expectedNumBuys, actualNumBuys, p);
	} else {
		printf("FAIL: numBuys expected %d buys, actual %d buys for player %d.\n", expectedNumBuys, actualNumBuys, p);
		allPass = 0;
	}
	
	// Verify player has +4 coins
	expectedNumCoins = baseG.coins + 4;
	actualNumCoins = G.coins;
	if (actualNumCoins == expectedNumCoins) {
		printf("PASS: numcoins expected %d cards, actual %d cards for player %d.\n", expectedNumCoins, actualNumCoins, p);
	} else {
		printf("FAIL: numCoins expected %d cards, actual %d cards for player %d.\n", expectedNumBuys, actualNumCoins, p);
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
	
	// Verify that the other players deck, hand, and discard did not change
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