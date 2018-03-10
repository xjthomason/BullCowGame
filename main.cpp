/* This is a console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user
interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

int main()
{
	PrintIntro();

	bool bPlayAgain = false;
	do
	{
		BCGame.Reset();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		std::cout << std::endl;
	} 
	while (bPlayAgain);

	system("pause");
	return 0; // exit the application
}

// introduce game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game\n";
	std::cout << std::endl;
	std::cout << "          }   {        ____  " << std::endl;
	std::cout << "          (o o)       (o o)  " << std::endl;
	std::cout << "   /-------\\ /         \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL | O          O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |             |------|  * " << std::endl;
	std::cout << "    ^      ^             ^      ^    " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for turns, while game is **NOT** won
	// and still have tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// loop continually to get valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry <<  " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Not an Isogram, please enter a word that only uses each letter once.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your answer in all lowercase letters.\n";
			break;
		default:
			break;
		}
		//std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // loop until no errors
	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "You won!\n\n";
	} else  {
		std::cout << "Bad luck!\n\n";
	}
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}
