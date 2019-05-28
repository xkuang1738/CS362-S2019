/*
Author: Xiao Kuang
Date: 5/5/2019
Last Updated: 5/5/2019
Description: HW3 cardtest4.c, testing dominion code cards. This file unit tests the code of council room card.  The player's hand and deck are set before each test case and is compared to the known correct result.  
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"
#include <stdlib.h>

#define TESTCARD "council room"

int main(){
	int testCounter = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int otherPlayer = 1;
	int handpos = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int choice1 = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	// clear gameState(s)
	memset(&G, 23, sizeof(struct gameState));

	// initialize the game
	initializeGame(numPlayers, k, seed, &G);
// PLAYER 1
	// set the deck up for testing
	G.deckCount[thisPlayer] = 10;	// 5 cards in deck
	int idx;
	for(idx = 0; idx < 10; idx++){
		G.deck[thisPlayer][idx] = 1;	// fill deck with 5 estate cards
	}
	// set up discard for testing
	G.discardCount[thisPlayer] = 0;
	// for(idx = 0; idx < 10; idx++){
	// 	G.discard[thisPlayer][idx] = duchy;
	// }

	// set hand as {smithy, province, estate, estate, estate}
	G.hand[thisPlayer][0] = council_room;
	// G.hand[thisPlayer][1] = province;
	for(idx = 1; idx < 5; idx++){
		G.hand[thisPlayer][idx] = 1;
	}

// PLAYER 2
	// set the deck up for testing
	G.deckCount[otherPlayer] = 10;	// 5 cards in deck
	for(idx = 0; idx < 10; idx++){
		G.deck[otherPlayer][idx] = 1;	// fill deck with 5 estate cards
	}
	
	// set hand as {estate, estate , estate, estate, estate}
	
	for(idx = 0; idx < 5; idx++){
		G.hand[otherPlayer][idx] = 1;
	}

	G.playedCardCount = 0;
	G.numActions = 1;
	G.numBuys = 1;
	G.handCount[otherPlayer] = 5;

// TESTING STARTS HERE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
	printf(">>>>>CARD TEST 4 START>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("Testing council room effect code:\n\n");
	// TEST CASE 1
	// Preconditions:
		// P1 Hand will have 5 cards: 1 council room, 4 estates, P2 Hand will have 5 estates
		// P1 Deck will have 10 cards: 10 estates, P2 Deck will have 10 cards: 10 estates
		// P1 Discard will have 0 cards, P2 Discard will have 0 cards
		// PlayedCardsCount will be 0:
		// numBuys will be 1 
	// Postcontitions:
		// P1 Hand will have 8 cards: 8 estates, P2 Hand will have 6 cards: 6 estates
		// P1 Deck will have 6 cards: 6 estates, P2 Deck will have 9 cards: 9 estates
		// P1 Discard will have 0 cards, P2 Discard will have 0 cards
		// PlayedCardsCount will be 1:
		// numBuys will be 2 		
	// * Play council room
	// * Gain 1 buy
	// * Draw 4 cards
	// * Other players draw 1 card
	// * Add to playedCards

	playCard(handpos, choice1, choice2, choice3, &G);

	printf("Test case 1: Testing all players drawing cards \n");

	if(G.handCount[thisPlayer] == 8){
		testCounter++;
	}else{
		printf("\tERROR>>> Expected hand count: 8\n\tActual hand count: %d\n", G.handCount[thisPlayer]);
	}
	if(G.deckCount[thisPlayer] == 6){
		testCounter++;
	}else{
		printf("\tERROR>>> Expected deck count: 6\n\tActual deck count: %d\n", G.deckCount[thisPlayer]);
	}
	if(G.discardCount[thisPlayer] == 0){
		testCounter++;
	}else{
		printf("\tERROR>>> Expected discard count: 0\n\tActual discard count: %d\n", G.discardCount[thisPlayer]);
	}
	if(G.playedCardCount == 1){
		testCounter++;
	}else{
		printf("\tERROR>>> Expected playedCards count: 1\n\tActual playedCards count: %d\n", G.playedCardCount);
	}
	if(G.numBuys == 2){
		testCounter++;
	}else{
		printf("\tERROR>>> Expected number of buys : 2\n\tActual number of buys: %d\n", G.numBuys);
	}
	if(G.handCount[otherPlayer] == 6){
		testCounter++;
	}else{
		printf("\tERROR>>> Expected hand count: 6\n\tActual hand count: %d\n", G.handCount[otherPlayer]);
	}
	if(G.deckCount[otherPlayer] == 9){
		testCounter++;
	}else{
		printf("\tERROR>>> Expected deck count: 9\n\tActual deck count: %d\n", G.deckCount[otherPlayer]);
	}
	if(G.discardCount[otherPlayer] == 0){
		testCounter++;
	}else{
		printf("\tERROR>>> Expected discard count: 0\n\tActual discard count: %d\n", G.discardCount[otherPlayer]);
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
