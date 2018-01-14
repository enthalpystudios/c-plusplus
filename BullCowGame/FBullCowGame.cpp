#pragma once

#include "FBullCowGame.h"
#include <map>

#define TMap std::map


FBullCowGame::FBullCowGame()
{
    Reset();
}

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "planet";
    
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}

int32 FBullCowGame::GetMaxTries() const
{
    TMap<int32, int32> WordLengthToMaxTries { {3, 4}, {4, 7}, {5, 10}, {6, 16}, {7, 20} };
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
    return MyCurrentTry;
}

bool FBullCowGame::IsGameWon() const
{
    return bGameIsWon;
}

int32 FBullCowGame::HiddenWordLength() const
{
    return MyHiddenWord.length();
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
    if (guess.length() != HiddenWordLength())
    {
        return EGuessStatus::NOT_CORRECT_SIZE;
    }
    else if (!IsLowerCase(guess))
    {
        return EGuessStatus::NOT_LOWER_CASE;
    }
    else if (!IsIsogram(guess))
    {
        return EGuessStatus::NOT_AN_ISOGRAM;
    }
    return EGuessStatus::OK;
}

bool FBullCowGame::IsIsogram(FString guess) const
{
    if (guess.length() <= 1) { return true; }
    TMap<char, bool> LetterSeen;
    for (auto Letter: guess)
    {
        Letter = tolower(Letter);
        if (LetterSeen[Letter])
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

bool FBullCowGame::IsLowerCase(FString guess) const
{
    for (auto Letter: guess)
    {
        if (!islower(Letter))
        {
            return false;
        }
    }
    return true;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;

    int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
    for (int32 HWCharIndex = 0; HWCharIndex < WordLength; HWCharIndex++)
    {
        for (int32 GCharIndex = 0; GCharIndex < WordLength; GCharIndex++)
        {
            if (guess[HWCharIndex] == MyHiddenWord[GCharIndex])
            {
                if (HWCharIndex == GCharIndex)
                {
                    BullCowCount.Bulls++;
                } else {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    bGameIsWon = (BullCowCount.Cows == 0 && BullCowCount.Bulls == WordLength);
    return BullCowCount;
}

