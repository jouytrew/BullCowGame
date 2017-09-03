/* Game logic
 * Simple guess the word game based on mastermind
 *
 */

#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map // Unreal syntax

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

// returns the number of tries based on the word length
int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 7}, {5, 10}, {6, 16}, {7, 21} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

// resets the game to default settings
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // must be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// returns whether or not input Guess is an isogram
bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) { return true; } // very short entries are passed through
	
	TMap<char, bool> LetterSeen; // setup out map
	for (auto Letter : Guess) 
	{
		Letter = tolower(Letter); // handle mixed case (why can't we do this in the guess?)
		if (LetterSeen[Letter]) // if it is in the map
		{
			return false;
		} 
		else 
		{
			LetterSeen[Letter] = true;
		}
	}
	
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter)) { return false; }
	}
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (Guess.length() != GetHiddenWordLength()) // if wrong length
	{
		return EGuessStatus::WRONG_LENGTH;
	}
	else if (!IsIsogram(Guess)) // if guess isn't an isogram
	{
		return EGuessStatus::NOT_ISOGRAM;
	} 
	else if (!IsLowercase(Guess)) // if not all lowercase
	{
		return EGuessStatus::NOT_LOWERCASE;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// Receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	for (int32 i = 0; i < WordLength; i++)
	{
		// compare against word
		for (int32 j = 0; j < WordLength; j++)
		{
			// If they match
			if (Guess[i] == MyHiddenWord[j])
			{
				(i == j) ? BullCowCount.Bulls++ : BullCowCount.Cows++;
				break;
			}
		}
	}
	BullCowCount.Bulls == WordLength ? bGameIsWon = true : bGameIsWon = false;
	return BullCowCount;
}
