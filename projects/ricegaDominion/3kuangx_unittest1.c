/*
Author: Xiao Kuang
Date: 5/4/2019
Last Updated: 5/4/2019
Description: HW3 unittest1.c, testing refactored code from HW2. This file tests the refactored code of adventurer card.  The player's hand and deck are set before each test case and is compared to the known correct result.  
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main(){
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

	// set hand as {adventurer, estate, estate, estate, estate}
	G.hand[thisPlayer][0] = adventurer;
	for(idx = 1; idx < 5; idx++){
		G.hand[thisPlayer][idx] = 1;
	}

// TESTING STARTS HERE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
	printf(">>>>>UNIT TEST 1 START>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("Testing adventurer refactored code:\n\n");
	// TEST CASE 1
	// deck = {$,X,X,X,X,X,X,X,$,$}
	// After adventurer played, +2 Treasures in hand, +0 cards in discard
	// copy initialized gameState to testG
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deck[thisPlayer][0] = gold;
	testG.deck[thisPlayer][8] = gold;
	testG.deck[thisPlayer][9] = gold;
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Test case 1: Top 2 cards of deck and bottom card are treasures.\n");

	if(testG.handCount[thisPlayer] == 7){
		testCounter++; //1
	}else{
		printf("\tERROR>>> Expected hand count: 7\n\tActual hand count: %d\n", testG.handCount[thisPlayer]);
	}
	if(testG.discardCount[thisPlayer] == 0){
		testCounter++; //2
	}else{
		printf("\tERROR>>> Expected discard count: 0\n\tActual discard count: %d\n", testG.discardCount[thisPlayer]);
	}
	// TEST CASE 2
	// deck = {$,$,X,X,X,X,X,X,X,$}
	// After adventurer played, +2 Treasures in hand, +7 cards in discard
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deck[thisPlayer][0] = gold;
	testG.deck[thisPlayer][1] = gold;
	testG.deck[thisPlayer][9] = gold;
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Test case 2: Top card of deck and bottom two cards are treasures.\n");

	if(testG.handCount[thisPlayer] == 7){
		testCounter++; //3
	}else{
		printf("\tERROR>>> Expected hand count: 7\n\tActual hand count: %d\n", testG.handCount[thisPlayer]);
	}
	if(testG.discardCount[thisPlayer] == 7){
		testCounter++; //4
	}else{
		printf("\tERROR>>> Expected discard count: 7\n\tActual discard count: %d\n", testG.discardCount[thisPlayer]);
	}

	// TEST CASE 3
	// deck = {$,$,$,X,X,X,X,X,X,X}
	// After adventurer played, +2 Treasures in hand, +7 cards in discard
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deck[thisPlayer][0] = gold;
	testG.deck[thisPlayer][1] = gold;
	testG.deck[thisPlayer][2] = gold;
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Test case 3: Bottom 3 cards of deck are treasures.\n");

	if(testG.handCount[thisPlayer] == 7){
		testCounter++; //5
	}else{
		printf("\tERROR>>> Expected hand count: 7\n\tActual hand count: %d\n", testG.handCount[thisPlayer]);
	}
	if(testG.discardCount[thisPlayer] == 7){
		testCounter++; //6
	}else{
		printf("\tERROR>>> Expected discard count: 7\n\tActual discard count: %d\n", testG.discardCount[thisPlayer]);
	}

	// TEST CASE 4
	// deck = {X,X,$,$,X,X,$,X,X,X}
	// After adventurer played, +2 Treasures in hand, +5 cards in discard
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deck[thisPlayer][2] = gold;
	testG.deck[thisPlayer][3] = gold;
	testG.deck[thisPlayer][6] = gold;
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	printf("Test case 4: From the top, the 4th, 7th and 8th cards are treasures.\n");
	if(testG.handCount[thisPlayer] == 7){
		testCounter++; //7
	}else{
		printf("\tERROR>>> Expected hand count: 7\n\tActual hand count: %d\n", testG.handCount[thisPlayer]);
	}
	if(testG.discardCount[thisPlayer] == 5){
		testCounter++; //8
	}else{
		printf("\tERROR>>> Expected discard count: 5\n\tActual discard count: %d\n", testG.discardCount[thisPlayer]);
	}

	// determine if all tests passed
	if(testCounter == 8){
		printf("ALL TESTS PASSED\n");
	}else{
	printf("********************\n");
	printf("TEST(S) FAILED\n");	
	printf("********************\n");
	}
	return 0;
}
