/*
 This is the console executable, that makes use of the BullCow class.
 This acts as the view in an MVC pattern, and is responsible for all user
 interaction. For Game logic, see FBullGameCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PrintGameSummary();
FText GetGuess();
void PlayGame();
bool AskToPlayAgain();
FText AskForValidGuess();

// Game instance
FBullCowGame BCGame;

int main()
{
    bool IsPlayAgain = false;
    do
    {
        PrintIntro();
        PlayGame();
        IsPlayAgain = AskToPlayAgain();
    } while (IsPlayAgain);
    return 0;
}

void PrintIntro()
{
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Welcome to Bulls & Cows, a fun word game." << std::endl;
    std::cout << "Can you guess the " << BCGame.HiddenWordLength() << " letter isogram I'm thinking off?" << std::endl;
    return;
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "Congratulations, you guessed the isogram!" << std::endl;
    }
    else
    {
        std::cout << "Bad luck, you did not guess the isogram!" << std::endl;
    }
}

void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() < MaxTries)
    {
        FText validGuess = AskForValidGuess();
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(validGuess);
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << std::endl;    
    }
    PrintGameSummary();
}

FText AskForValidGuess()
{
    int32 currentTry = BCGame.GetCurrentTry();
    EGuessStatus status;
    FText guess = "";
    do
    {
        std::cout << "Try " << currentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
        guess = GetGuess();
        status = BCGame.CheckGuessValidity(guess);
        switch (status) {
            case EGuessStatus::NOT_AN_ISOGRAM:
                std::cerr << "The word you inserted is not an isogram. Try again!" << std::endl;
                break;
            case EGuessStatus::NOT_CORRECT_SIZE:
                std::cerr << "The word you inserted is not of correct length. Remember it needs to have " << BCGame.HiddenWordLength() << " letters!" << std::endl;
                break;
            case EGuessStatus::NOT_LOWER_CASE:
                std::cerr << "All letters need to be lower case!" << std::endl;
                break;
            default:
                break;
        }
    } while (status != EGuessStatus::OK);
    std::cout << "Your guess was: " << guess << std::endl;
    return guess;
}

bool AskToPlayAgain()
{
    FText response = "";
    std::cout << "Do you want to play again? [y/n]: ";
    std::getline(std::cin, response);
    return 'y' == response[0] || 'Y' == response[0];
}

FText GetGuess()
{
    FText guess = "";
    std::getline(std::cin, guess);
    return guess;
}
