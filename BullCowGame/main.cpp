/* This is the console executable, that makes use of the BullCow class
 * This acts as the view in a MVC patter, and is responsible for all 
 * user interaction. For game logic see the FBullCowGame class.
 */
#pragma once // not sure if this is required in the main file

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes
void PrintIntro();
void PrintGameSummary();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game, which is reused

// application entry point
int main()
{
	bool bPlayAgain = false;
	PrintIntro();

	do
	{
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0; // exits application
}

// plays one game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// is NOT won and haven't used all tries
	while ( !BCGame.IsGameWon() && (BCGame.GetCurrentTry() <= MaxTries) )
	{
		FText Guess = GetValidGuess(); 
		
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
	}

	PrintGameSummary();

	return;
}

// loop until user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::INVALID;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry " << CurrentTry << "/" << BCGame.GetMaxTries() << " - Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Please enter a word with no repeating letters." << std::endl;
			break;
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl;
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please only use lowercase." << std::endl;
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK); 
	return Guess;
}

// prompt the user on whether or not they wish to play again
bool AskToPlayAgain()
{
	std::cout << "\nWould you like to play again with the same word (y/n): ";
	FText UserI = "";
	std::cin >> UserI;

	std::cin.ignore(10000, '\n'); // ignore cin buffer, otherwise cin carries over to next game, don't know why

	return (UserI[0] == 'y' || UserI[0] == 'Y');
}

// introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "              }___{                        " << std::endl;
	std::cout << "              \\o o/                        " << std::endl;
    std::cout << "         ______\\ /       ________          " << std::endl;
	std::cout << "       /|       O      _/        |\\        " << std::endl;
	std::cout << "      / |_______|     o /|______ | \\       " << std::endl;
	std::cout << "     o  ||     ||     |/ ||     ||  o      " << std::endl;
	std::cout << "        ||     ||     O  ||     ||         " << std::endl;
    std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	return;
}

// summarise game results
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\nWell done! You've won!" << std::endl;
	}
	else {
		std::cout << "\nYou're out of turns... better luck next time." << std::endl;
	}
	return;
}