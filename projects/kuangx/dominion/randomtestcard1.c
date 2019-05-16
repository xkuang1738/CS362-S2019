#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"
#include <stdlib.h>

#define TESTCARD "smithy"

// https://stackoverflow.com/questions/2509679/how-to-generate-a-random-integer-number-from-within-a-range
int rand_interval(int min, int max)
{
	int r;
	const int range = 1 + max - min;
	const int buckets = RAND_MAX / range;
	const int limit = buckets * range;

	/* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
	do
	{
		r = rand();
	} while (r >= limit);

	return min + (r / buckets);
}

int main()
{
	// SET HOW MANY TESTS TO RUN
	const int TESTCOUNTER = 50;
	srand(time(NULL));

	int idx, jdx, kdx = 0;

	int seed = 1000;
	int numPlayers = 2;
	int handpos = 0, choice1 = 0, bonus = 0;

	struct gameState G, testG, beforeG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	// clear gameState(s)
	memset(&G, 23, sizeof(struct gameState));

	// initialize the game
	initializeGame(numPlayers, k, seed, &G);

	for (jdx = 0; jdx < TESTCOUNTER; jdx++)
	{
		memcpy(&testG, &G, sizeof(struct gameState));
		// use testG now for gameState testing

		// set up hand for test
		testG.handCount[0] = rand_interval(1, 20);
		for (idx = 0; idx < testG.handCount[0]; idx++)
		{
			// for each card in hand make it random
			testG.hand[0][idx] = rand_interval(0, 25);
		}
		// have a known card be smithy
		handpos = rand_interval(0, testG.handCount[0] - 1);
		testG.hand[0][handpos] = 13;

		// set up deck for test
		testG.deckCount[0] = rand_interval(5, 20);
		for (idx = 0; idx < testG.deckCount[0]; idx++)
		{
			// for each card in deck make it random
			testG.deck[0][idx] = rand_interval(0, 25);
		}

		// set up discard for test
		testG.discardCount[0] = rand_interval(5, 20);
		for (idx = 0; idx < testG.discardCount[0]; idx++)
		{
			// for each card in deck make it random
			testG.discard[0][idx] = rand_interval(0, 25);
		}

		// make a copy of gameState before card is played so we have something to compare to
		memcpy(&beforeG, &testG, sizeof(struct gameState));

		cardEffect(smithy, choice1, choice1, choice1, &testG, handpos, &bonus);

		// after card is played, check gamestate before and after, compare with expected results
		assert(testG.handCount[0] == (beforeG.handCount[0] + 2));
		assert(testG.deckCount[0] == (beforeG.deckCount[0] - 3));
		assert(testG.playedCards[0] == smithy);
		assert(testG.playedCardCount == 1);
	}

	// if reach here then all tests passed
	printf("\nSMITHY RANDOM TESTS PASSED\n");

	return 0;
}

