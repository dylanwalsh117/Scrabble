
#define _CRT_SECURE_NO_DEPRECATE
#include <string.h>
#include <stdio.h>
#include<stdlib.h>

using namespace std;
void generate_letters(int number, char* destination) {
	char vowels[] = { 'a', 'e', 'i', 'o', 'u' };
	int i;
	unsigned int rand_seed;
	printf("Number < 1000:\n");
	scanf_s("%d", &rand_seed); // initialise the PRNG
	getchar();
	srand(rand_seed);
	// Half of the letters should be vowels
	for (i = 0; i < number / 2; i++, destination++) *destination = vowels[rand() % 5];
	for (; i < number; i++, destination++) *destination = rand() % 26 + 'a';
}
int read_array_from_file(const char* filepath, int* array, int array_length) {
	FILE* file;
	int i;
	if ((file = fopen(filepath, "r")) == NULL) {

		return -1;
	}
	for (i = 0; i < array_length; i++) {
		if (fscanf(file, "%d", &array[i]) == EOF)
			break;
	}
	return i;
}
int main() {

	// array for random seven characters
	char * arr;
	arr = (char*)malloc(sizeof(char) * 7);
	generate_letters(7, arr);
	
	//array for worth of characters
	int* value;
	value = (int*)malloc(sizeof(int) * 26);
	read_array_from_file("letter_values.txt", value, 26);

	//Array for frequency of random characters generated
	short int alphaFreq[26] = { 0 };
	for (int i = 0; i < 7; i++) {
		alphaFreq[arr[i]-'a']++;
	}

	//Print characters with count
	for (int i = 0; i < 26; i++) {
		if(alphaFreq[i]!=0)
			printf("%c-->%d\n",i+'a', alphaFreq[i]);
	}


	char input[1024][20];
	int wordIndex = 0;
	int worth[1024] = { 0 };
	char flag = 'y';
	int total = 0;

	//terminate when other than 'y'
	while (flag == 'y') {
		//Array for the characters that are not available and initilize all array with '\n'
		char missing[1024] = {'\n'};
		int missingIndex = 0;

		//copy of available character frequency
		short int alphaFreqCopy[26] = { 0 };
		for (int i = 0; i < 7; i++) {
			alphaFreqCopy[i] = alphaFreq[i];
		}

		printf("Input word:");
		gets_s(input[wordIndex]);


		//calculate worth and store missing character if any in user input
		//it decrement freq of character if it found in input string
		// else if that character is not available it put it into missing array

		//wordIndex][i] - 'a'
		// ascii of a is 97 so by subtraction we from index from 0-25
		for(int i=0;i<strlen(input[wordIndex]);i++)
		{
			if (alphaFreqCopy[input[wordIndex][i]-'a'] != 0) {
				worth[wordIndex] += value[input[wordIndex][i] - 'a'];
				alphaFreqCopy[input[wordIndex][i]-'a']--;
			}
			else {
				missing[missingIndex++] = input[wordIndex][i];
			}
		}
		missing[missingIndex++] = '\n';

		total += worth[wordIndex];
		printf("You used: %s, Worth: %d. Current Total: %d \n", input[wordIndex],worth[wordIndex],total);
		if(missingIndex > 1)
			printf("Missing:%s", missing);
		printf("Try again? (y/n)");
		flag=getchar();

		// to clear input buffer
		while ((getchar()) != '\n');
		wordIndex++;
	}
	
	printf("\n\n****************************\nYou provided the following words\n");
	for (int i = 0; i < wordIndex; i++) {
		printf("%s -> %d\n", input[i], worth[i]);
	}
	printf("Total Score: %d\n", total);
	return 0;
}