#pragma once

#include <string>
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    OK,
    NOT_AN_ISOGRAM,
    NOT_CORRECT_SIZE,
    NOT_LOWER_CASE
};

class FBullCowGame
{
public:
    FBullCowGame(); // constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    bool IsGameWon() const;
    int32 HiddenWordLength() const;
    EGuessStatus CheckGuessValidity(FString) const;
    bool IsIsogram(FString) const;
    bool IsLowerCase(FString) const;
    
    void Reset();
    FBullCowCount SubmitValidGuess(FString);  // assumes valid guess
    
    
private:
    // see constructor for initialisation
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
};
