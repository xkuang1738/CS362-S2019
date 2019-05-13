#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
//https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
// used fisher yates shuffle to randomly shuffle the array around, sourced from geeksforgeeks
void swap (char *a, char *b) 
{ 
    char temp = *a; 
    *a = *b; 
    *b = temp; 
} 
  
void randomize ( char arr[], int n ) 
{ 
    // Use a different seed value so that we don't get same 
    // result each time we run this program 
	int i;
    // Start from the last element and swap one by one. We don't 
    // need to run for the first element that's why i > 0 
    for (i = n-1; i > 0; i--) 
    { 
        // Pick a random index from 0 to i 
        int j = rand() % (i+1); 
  
        // Swap arr[i] with the element at random index 
        swap(&arr[i], &arr[j]); 
    } 
} 
char inputChar()
{
    // TODO: rewrite this function

    char charArr[10] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};
	randomize(charArr, 10);
    return charArr[5];
}

char *inputString()
{
    // TODO: rewrite this function
	int idx;
	char* str = calloc(6, sizeof(char));
	char charArr[4] = {'r', 'e', 's', 't'};
	for(idx = 0; idx < 5; idx++){
		randomize(charArr, 4);
		str[idx] = charArr[1];
	}
	str[5] = '\0';
    return str;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      free(s);
      exit(200);
    }
    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
