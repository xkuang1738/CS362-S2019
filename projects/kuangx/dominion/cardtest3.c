/*
Author: Xiao Kuang
Date: 5/5/2019
Last Updated: 5/5/2019
Description: HW3 cardtest3.c, testing dominion code cards. This file unit tests the code of salvager card.  The player's hand and deck are set before each test case and is compared to the known correct result.  
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"
#include <stdlib.h>

#define TESTCARD "salvager"

int main(){
	int testCounter = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	// set choice1 to choose index [1], province card to trash
	int handpos = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int choice1 = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	// clear gameState(s)
	memset(&G, 23, sizeof(struct gameState));

	// initialize the game
	initializeGame(numPlayers, k, seed, &G);

	// set the deck up for testing
	G.deckCount[thisPlayer] = 5;	// 5 cards in deck
	int idx;
	for(idx = 2; idx < 5; idx++){
		G.deck[thisPlayer][idx] = 1;	// fill deck with 5 estate cards
	}

	// set up discard for testing
	G.discardCount[thisPlayer] = 0;
	// for(idx = 0; idx < 10; idx++){
	// 	G.discard[thisPlayer][idx] = duchy;
	// }

	// set hand as {smithy, province, estate, estate, estate}
	G.hand[thisPlayer][0] = salvager;
	G.hand[thisPlayer][1] = province;
	for(idx = 2; idx < 5; idx++){
		G.hand[thisPlayer][idx] = 1;
	}

	G.playedCardCount = 0;
	G.coins = 0;
	G.numActions = 1;

// TESTING STARTS HERE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
	printf(">>>>>CARD TEST 3 START>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("Testing salvager effect code:\n\n");
	// TEST CASE 1
	// Preconditions:
	// Set hand, deck, and discard to known cards/values
		// Hand will be 5 cards, 3 estate victory cards, 1 province victory card in [1] position, and 1 smithy kingdom card in [0] position
		// deck will be have 5 cards, all estate victory cards
		// discard will be empty
		// playedCards will be empty
		// coins will be 0
	// Postcontitions:
		// Hand will have 3 cards: 3 estates
		// Deck will have 5 cards: 5 estates
		// Discard will have 0 cards: 
		// playedCards will have 1 salvager
		// coins will be 8
		
	// * Play salvager
	// * Trash province
	// * Gain 8 coin
	// * Satisfy salvager effects
	// * Add to playedCards

	playCard(handpos, choice1, choice2, choice3, &G);

	printf("Test case 1: Testing trashing of card and gaining of coin \n");
	printf("\tExpected hand count: 3\n\tActual hand count: %d\n", G.handCount[thisPlayer]);

	printf("\tExpected deck count: 5\n\tActual deck count: %d\n", G.deckCount[thisPlayer]);

	printf("\tExpected discard count: 0\n\tActual discard count: %d\n", G.discardCount[thisPlayer]);

	printf("\tExpected playedCards count: 1\n\tActual playedCards count: %d\n", G.playedCardCount);

	printf("\tExpected coins : 8\n\tActual coins: %d (please see hw3 pdf)\n", G.coins);


	// print if tests passed or not. If passed, increment testCounter
	if(G.handCount[thisPlayer] == 3 && G.deckCount[thisPlayer] == 5 && G.discardCount[thisPlayer] == 0 && G.playedCardCount == 1 && G.coins == 8){
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
	printf(">>>>>CARD TEST 3 END>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	return 0;
}
