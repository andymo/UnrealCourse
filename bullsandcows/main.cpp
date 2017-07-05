#include <iostream>
#include <string>
#include "FBullCowGame.h"

using int32 = int;
using FText = std::string;

void PrintWelcomeMessage();
void PlayGame();
bool PlayAgain();
FText GetValidGuess();
FText GetInput(FText Prompt);
void PrintBullCowCount(FBullCowCount Count);
void PrintSummary();

FBullCowGame BCGame;


int main() {
    PrintWelcomeMessage();

    do {
        PlayGame();
    } while (PlayAgain());

    return 0;
}


void PrintWelcomeMessage() {
    std::cout << "Welcome to Bulls and Cows!" << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter word?" << std::endl;
}


void PlayGame() {
    BCGame.Reset();

    while (!BCGame.IsGameWon() && BCGame.GetCurrentTries() < BCGame.GetMaxTries()) {
        FText Guess = GetValidGuess();
        FBullCowCount Count = BCGame.SubmitGuess(Guess);
        PrintBullCowCount(Count);
    }

    PrintSummary();
}


bool PlayAgain() {
    FText Choice = GetInput("Would you like to play again? (y/n) ");
    return !Choice.compare("y");
}


FText GetValidGuess() {
    FText Guess;
    EGuessValidity GuessStatus;

    do {
        std::cout << "\nGuess " << BCGame.GetCurrentTries() << " of " << BCGame.GetMaxTries();
        Guess = GetInput("Enter your guess: ");
        GuessStatus = BCGame.GetGuessValidity(Guess);

        switch(GuessStatus) {
        case EGuessValidity::INVALID_LENGTH:
            std::cout << "Please enter a word that is " << BCGame.GetHiddenWordLength() << " letters" << std::endl;
            break;
        case EGuessValidity::NOT_ISOGRAM:
            std::cout << "Please enter an isogram." << std::endl;
            break;
        default:
            break;
        }
    } while (GuessStatus != EGuessValidity::OK);

    return Guess;
}


FText GetInput(FText Prompt) {
    FText Input = "";

    std::cout << "\n" << Prompt;
    std::getline(std::cin, Input);
    std::transform(Input.begin(), Input.end(), Input.begin(), ::tolower);

    return Input;
}


void PrintBullCowCount(FBullCowCount Count) {
    std::cout << "Bulls: " << Count.NumBulls << "; Cows: " << Count.NumCows << std::endl;
}


void PrintSummary() {
    if (BCGame.IsGameWon())
        std::cout << "\n!!! Congratulations on a meaningless victory !!!" << std::endl;
    else
        std::cout << "\nYou lost because you are a terrible human being." << std::endl;
}
