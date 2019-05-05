/*
Author: Xiao Kuang
Date: 5/5/2019
Last Updated: 5/5/2019
Description: HW3 cardtest1.c, testing dominion code cards. This file unit tests the code of adventurer card.  The player's hand and deck are set before each test case and is compared to the known correct result.  
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

	// initialize the game
	initializeGame(numPlayers, k, seed, &G);

	// set the deck up for testing
	G.deckCount[thisPlayer] = 5;	// 5 cards in deck
	int idx;
	for(idx = 0; idx < 5; idx++){
		G.deck[thisPlayer][idx] = 1;	// fill deck with 5 estate cards
	}

	// set up discard for testing
	G.discardCount[thisPlayer] = 2;
	G.discard[thisPlayer][0] = gold;
	G.discard[thisPlayer][1] = gold;

	// set hand as {adventurer, estate, estate, estate, estate}
	G.hand[thisPlayer][0] = adventurer;
	for(idx = 1; idx < 5; idx++){
		G.hand[thisPlayer][idx] = 1;
	}

// TESTING STARTS HERE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
	printf(">>>>>CARD TEST 1 START>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("Testing adventurer effect code:\n\n");
	// TEST CASE 1
	// Preconditions:
	// Set hand, deck, and discard to known cards/values
		// Hand will be 5 cards, 4 estate victory cards and 1 adventurer kingdom card in [0] position
		// deck will be 5 estate cards
		// discard will be 2 gold treasure cards
	// Postcontitions:
		// Hand will have 7 cards: 5 cards to start including adventurer, 5 estates drawn, 2 treasures drawn, discard 5 estates 
		// Deck will have 0 cards: 5 estates to start with, they all get drawn; Discard is shuffled and 2 gold added to deck; Both gold drawn
		// Discard will have 5 cards: 2 gold to start with, both gold get added to deck, 5 non-treasure cards drawn from adventurer discarded
		
	// * Play adventurer
	// * Draw all cards in deck
	// 		* Store in temphand[]
	// * No more cards in deck
	// 		* Shuffle discard and use as deck
	// * Draw gold
	// 		* drawntreasure++
	// * Draw gold
	// 		* drawntreasure++
	// * Satisfy adventurer effects
	// * Discard cards in temphand[]

	playCard(handpos, choice1, choice2, choice3, &G);

	printf("Test case 1: No treasures in deck, two treasures in discard. Testing when deck depleted and shuffle of discard is necessary. \n");
	printf("\tExpected hand count: 7\n\tActual hand count: %d\n", G.handCount[thisPlayer]);

	printf("\tExpected deck count: 0\n\tActual deck count: %d\n", G.deckCount[thisPlayer]);

	printf("\tExpected discard count: 5\n\tActual discard count: %d\n", G.discardCount[thisPlayer]);

	

	// print if tests passed or not. If passed, increment testCounter
	if(G.handCount[thisPlayer] == 7  && G.deckCount[thisPlayer] == 0 && G.discardCount[thisPlayer] == 5){
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
	printf(">>>>>CARD TEST 1 END>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	return 0;
}
