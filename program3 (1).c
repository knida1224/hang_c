/*Kyle Nida
Z 23410025
COP2220
04/10/2016
program3.c-[HANGMAN GAME]*/

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <ctype.h>
#include <string.h> //strcmp, //strlen
#define WSIZE 30

// Function Prototype

//Determines if the player wants to play again 
void Quit(char *againPtr);

//Displays instructions
void Rules();

//initializes the word to be guessed to *** based on word size 
void InitializeWord(char starWord[], int wordsize);

//play a round of the game, 
//returns a 1 if the user wins and a 0 if the user did not win
int PlayOneRound(char solutionWord[], char starWord[], int len);

//gets a letter guess from the user
void GetLetter(char *letterPtr);


//compares two char arrays returns 1 if match, 0 if dont match 
int CompareArrays(char wordGuess[], char solutionWord[]);

//notifies the user if they won or lost 
void WonLost(char solutionWord[], int win);

//replaces the star with the letter guessed
//returns a 1 if the letter is in the word, returns a 0 if the letter //is not in the word

int PlaceLetter(char solutionWord[], char starWord[], char target);

//changes a word to upper or lower case 
void ChangeCase(char word[]);

//draws the hangman 
void DrawHangman(int num);

int main()
{
	char again = 0;
	char starWord[WSIZE] ;
	char solutionWord[WSIZE] ;
	int len;
	int win = 0;

	FILE*inPtr;
	inPtr = fopen("hangmanWords.txt", "r");// file opening
	Rules();// calling rules to main funtion
	//loop 
	do {
		fscanf(inPtr, " %s", &solutionWord);// reading solutionword
		ChangeCase(solutionWord);// changing upper or lower case
		len = strlen(solutionWord);// length of the solution word
		InitializeWord(starWord, len);// intializing star == word size
		win=PlayOneRound(solutionWord, starWord, len);// calling function to playoneround 
		WonLost(solutionWord, win);// notify user if they lose or win

		
		Quit(&again);// calling quit function 
		again = toupper(again);
	} while (again == 'n' || again == 'N');
	{
		printf("\t\n=======================THANK YOU!!!=======================\n");

	}
	fclose(inPtr);// closing file Ptr
	return 0;

}

//Determines if the player wants to play again 
void Quit(char *againPtr)
{
	char exit;
	printf("\n\n\n WOULD YOU LIKE TO QUIT FROM HANGMAN GAME? (Y/N): ");
	scanf(" %c", &exit);
	*againPtr = exit;
	

}
//Displays instructions
void Rules()
{
	//greet
	printf("\t\tWELCOME TO HANGMAN GAME\n");
	printf("\t\t~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	//rules
	printf("\tINSTRUCTION FOR HOW TO PLAY HANGMAN GAME\n");
	printf("\t*****************************************\n");
	printf("\n  1) YOU WILL SEE GUESSED WORDS IN STAR");
	printf("\n  2) YOU HAVE TO GUESS LETTER ONE BY ONE");
	printf("\n  3) THERE ARE SIX CHANCES TO GET CORRECT THE LETTERS.");
	printf("\n  4) IF YOU CORRECT ALL LETTERS THEN YOU CAN ENTER THE WORD COMPLETELY. ");
	printf("\n  5) IF YOU GUESS SIX TIMES  WRONG LETTER GAME WILL BE OVER AND SHOW THE WORD");
	printf("\n  6) IF YOU ENTER GUESS WORD RIGHT THEN ALSO GAME OVER AND CONGRATULATED YOU!!\n");
	printf("\t\n========================================================\n");
}
//initializes the word to be guessed to *** based on word size 
void InitializeWord(char starWord[], int wordsize)
{

	for (int i = 0; i < wordsize; i++) {
		starWord[i] = '*';// star char
		starWord[wordsize] = '\0';//  null char
	}

}
//play a round of the game, 
//returns a 1 if the user wins and a 0 if the user did not win
int PlayOneRound(char solutionWord[], char starWord[], int len)
{
	int let;
	int match = 0;
	char letter[WSIZE] = { 0 };
	char GuessWord[WSIZE];
	int wrongletter = 0;
	int Maxtries = 6;
	char target;
	InitializeWord(starWord, len);
	
	for (wrongletter = 0; wrongletter < Maxtries; wrongletter++)// loop
	{
		
		printf("\n\nHERE IS YOUR GUESS WORD: ");// ask the user to enter the guess word
		printf("%s", starWord);// masking the words
		GetLetter(&target);// getting letter from the user and passed into target.
		let=PlaceLetter(solutionWord, starWord, target);// function call to get place the letter
		if (let == 1) //conditions
		{
			printf("YOUR LETTER: %c  IS IN THE WORD!!", target);// displaying the letterin the word 
		}
		else
		{ 
			printf("\nYOUR LETTER: %c  IS NOT IN THE WORD!!", target);//displaying the letter not in the word
		}
		printf("\nGUESS WORD:%s\n",starWord);// showing guess word in '*'
		printf("\nENTER THE WORD:");//asking user the user to enter the word
		scanf(" %s", GuessWord);// getting guess word from the user
		ChangeCase(GuessWord);// changing  word to upper or lower case
		match = CompareArrays(GuessWord, solutionWord);// comparing the guess word and solution word
		printf("\nYOUR GUESS WORD ENTERED WAS %s \n", GuessWord);// displaying theuser enter guess word 
		if (match == 0 )//conditions for wrong
		{
			
			printf("\nSORRY TRY AGAIN!");
			printf("\nYOU HAVE  %d CHANCES LEFT", Maxtries -1-wrongletter);// subtracting chance left from max tries when u make incorrect guess
			DrawHangman(wrongletter);// drawing hangman according to wrong letters
		}
		else if (match == 1) // condition for right
		{
			printf("\nTHAT WORD IS CORRECT!");
			return 1;

		}
		printf("\t\n\n    <==========**================**==========>\n");
		letter[wrongletter] = target;
		printf("\n\nHERE ARE THE LETTERS YOU HAVE SO FAR: ");// printing out all the user input letters so far
		for (int i = 0; i<strlen(letter); i++) {
			printf(" %c", letter[i]);
		}
	}return 0;
}
//gets a letter guess from the user
void GetLetter(char *letterPtr)
{
	char Getl;
	printf("\nENTER A LETTER GUESS: ");// asking user  for Let guess
	scanf(" %c", &Getl);// saving the letter and read
	Getl = toupper(Getl);// change case
	printf("\nYOU ENTERED: %c\n", Getl);// display the word user enter
	*letterPtr = Getl;// Ptr to Getl.
}

//replaces the star with the letter guessed
//returns a 1 if the letter is in the word, returns a 0 if the letter //is not in the word

int PlaceLetter(char solutionWord[], char starWord[], char target)

{
	int value = 0;
	int len = strlen(solutionWord);// length  of the solution word
	for (int i = 0; i < len; i++)
	{
		if (target == solutionWord[i])
		{
			value = 1;
			starWord[i] = target;
			
		}
	}
	return value;
}

//changes a word to upper or lower case 
void ChangeCase(char word[])
{
	int len = strlen(word);
	int i;
	for (i = 0; i < len; i++) {
		word[i] = toupper(word[i]);

	}
}
//compares two char arrays returns 1 if match, 0 if dont match 
int CompareArrays(char wordGuess[], char solutionWord[])

{
	if (strcmp(wordGuess, solutionWord) == 0)
	{
		return 1;
	}
	else  return 0;

}

//notifies the user if they won or lost 
void WonLost(char solutionWord[], int win)
{
	if (win == 1) {
		printf("\n\n\n========>CONGRATULATIONS\n");
			printf("                      YOU WON THIS GAME!<===========\n");
	}
	else if (win == 0) {

		printf("\n\n==========>SORRY YOU LOST THIS ROUND.THE CORRECT WORD IS %s<==============\n\n ",solutionWord);
	}
}

//draws the hangman 
void DrawHangman(int num)
{

	if (num == 5)
	{
		printf("\t\n\n===========>Sorry Try agian!!!!<===========");
		printf("\t\n\nDRAWING 6:  ==========>FULL BODY<===========\n");
		
	}
	else if (num == 4)
	{
		printf("\n\nDRAWING 5:==========>LEFT HAND <===========\n");
	}
	else if (num == 3)
	{
		printf("\n\nDRAWING 4:==========>RIGHT HAND <===========\n");
	}
	else if (num == 2)
	{
		printf("\n\nDRAWING 3:==========>LEFT LEG AND RIGHT LEG <===========\n");
	}
	else if (num ==1)
	{
		printf("\n\nDRAWING 2:==========>BODY <===========\n");
	}
	else if (num == 0)
	{
		printf("\n\nDRAWING 1:==========>HEAD<=============\n");
	}
}

