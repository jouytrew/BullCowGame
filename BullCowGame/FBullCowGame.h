#pragma once

#include <string>

// Unreal syntax
using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows  = 0;
};
 
enum class EGuessStatus
{
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE,
	INVALID
};
 
class FBullCowGame 
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();

	FBullCowCount SubmitValidGuess(FString);


// ignore private for now
private:
	// see constructor
	int32 MyCurrentTry = 1;
	int32 MyMaxTries = 5;
	FString MyHiddenWord = "default";
	bool bGameIsWon = false;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};