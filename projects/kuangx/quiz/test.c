#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
// test program to test the functions
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

int main(){
	int idx, n = 20;
    srand ( time(NULL) ); 
	char* str;
	// for(idx = 0; idx < n; idx++){
	// 	 str= inputString();
	// 	printf("%s\n", str);
	// }
	char s;
	for(idx = 0; idx < n; idx++){
		s = inputChar();
		printf("%c\n", s);
	}
	free(str);
	return 0;
}
