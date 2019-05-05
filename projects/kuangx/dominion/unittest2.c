/*
Author: Xiao Kuang
Date: 5/4/2019
Last Updated: 5/5/2019
Description: HW3 unittest2.c, testing refactored code from HW2. This file tests the refactored code of smithy card.  The player's hand and deck are set as 5 and 10, respectively and checked against correct result. 
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main(){

	// Preconditions: 5 cards in hand, including smithy, have 10 cards in deck
	// Postconditions: +3 (7 total) cards in hand, 7 cards in deck

	// Set up game for test
	int testCounter = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	// clear gameState(s)
	memset(&G, 23, sizeof(struct gameState));
	memset(&testG, 23, sizeof(struct gameState));

	// initialize the game
	initializeGame(numPlayers, k, seed, &G);

	// set the deck up for testing
	G.deckCount[thisPlayer] = 10;	// 10 cards in deck
	int idx;
	for(idx = 0; idx < 10; idx++){
		G.deck[thisPlayer][idx] = 1;	// fill deck with 10 estate cards
	}

	G.discardCount[thisPlayer] = 0;

	// set hand as {smithy, estate, estate, estate, estate}
	G.hand[thisPlayer][0] = smithy;
	for(idx = 1; idx < 5; idx++){
		G.hand[thisPlayer][idx] = 1;
	}

	G.handCount[thisPlayer] = 5;

// TESTING STARTS HERE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	printf(">>>>>UNIT TEST 2 START>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("Testing smithy refactored code:\n\n");
	cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);
	printf("Test case 1: Smithy is played, effect is: +3 cards\n");
	printf("\tExpected hand count: 7\n\tActual hand count: %d\n", G.handCount[thisPlayer]);
	printf("\tExpected deck count: 7\n\tActual deck count: %d\n", G.deckCount[thisPlayer]);
	if(G.handCount[thisPlayer] == 7 && G.deckCount[thisPlayer] == 7){
		testCounter++;
		printf("\tTEST PASSED\n");
	}else{
		printf("\tTEST FAILED\n");
	}

	// determine if all tests passed
	printf("********************\n");
	if(testCounter == 1){
		printf("ALL TESTS PASSED\n");
	}else{
		printf("TEST(S) FAILED\n");
	}
	printf("********************\n");
	printf(">>>>>UNIT TEST 2 END>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

	return 0;
}
