/*
Author: Xiao Kuang
Date: 5/5/2019
Last Updated: 5/5/2019
Description: HW3 cardtest2.c, testing dominion code cards. This file unit tests the code of smithy card.  The player's hand and deck are set before each test case and is compared to the known correct result.  
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
	G.deckCount[thisPlayer] = 0;	// 0 cards in deck, will force to shuffle and add discard to deck
	int idx;
	// for(idx = 0; idx < 5; idx++){
	// 	G.deck[thisPlayer][idx] = 1;	// fill deck with 5 estate cards
	// }

	// set up discard for testing, 10 duchy victory cards
	G.discardCount[thisPlayer] = 10;
	for(idx = 0; idx < 10; idx++){
		G.discard[thisPlayer][idx] = duchy;
	}

	// set hand as {smithy, estate, estate, estate, estate}
	G.hand[thisPlayer][0] = smithy;
	for(idx = 1; idx < 5; idx++){
		G.hand[thisPlayer][idx] = 1;
	}

	G.playedCardCount = 0;

// TESTING STARTS HERE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
	printf(">>>>>CARD TEST 2 START>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("Testing smithy effect code:\n\n");
	// TEST CASE 1
	// Preconditions:
	// Set hand, deck, and discard to known cards/values
		// Hand will be 5 cards, 4 estate victory cards and 1 smithy kingdom card in [0] position
		// deck will be empty, 0 cards
		// discard will be 10 duchy victory cards
		// playedCards will be empty
	// Postcontitions:
		// Hand will have 7 cards: 5 cards to start, 3 duchy drawn, 1 smithy added to playedCards[]
		// Deck will have 7 cards: 0 cards to start, 10 duchy cards from discard get shuffled and added to deck, top 3 duchy cards drawn
		// Discard will have 0 cards: 10 cards to start, all discard cards get shuffled and added to deck
		// playedCards will have 1 smithy
		
	// * Play smithy
	// * No more cards in deck
	// 		* Shuffle discard and use as deck
	// * Draw 3 cards from deck
	// * Satisfy smithy effects
	// * Add to playedCards

	playCard(handpos, choice1, choice2, choice3, &G);

	printf("Test case 1: No cards in deck, 10 duchy victory cards in discard. Testing when deck depleted and shuffle of discard is necessary. \n");

	if(G.handCount[thisPlayer] == 7){
		testCounter++; //1
	}else{
		printf("\tERROR>>> Expected hand count: 7\n\tActual hand count: %d\n", G.handCount[thisPlayer]);
	}
	if(G.deckCount[thisPlayer] == 7){
		testCounter++; //2
	}else{
		printf("\tERROR>>> Expected deck count: 7\n\tActual deck count: %d\n", G.deckCount[thisPlayer]);
	}
	if(G.discardCount[thisPlayer] == 0){
		testCounter++; //3
	}else{
		printf("\tERROR>>> Expected discard count: 0\n\tActual discard count: %d\n", G.discardCount[thisPlayer]);
	}
	if(G.playedCardCount == 1){
		testCounter++; //4
	}else{
		printf("\tERROR>>> Expected played card count: 1\n\tActual played card count: %d\n", G.playedCardCount);
	}
// determine if all tests passed
	if(testCounter == 4){
		printf("ALL TESTS PASSED\n");
	}else{
	printf("********************\n");
	printf("TEST(S) FAILED\n");	
	printf("********************\n");
	}
	return 0;
}
