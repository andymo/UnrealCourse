#include "FBullCowGame.h"

using int32 = int;


FBullCowGame::FBullCowGame() {
    Reset();
}


int32 FBullCowGame::GetMaxTries() const { return MaxTries; }
int32 FBullCowGame::GetCurrentTries() const { return CurrentTries; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }


void FBullCowGame::Reset() {
    const FString HIDDEN_WORD = "planet";
    constexpr int32 MAX_TRIES = 5;

    bGameWon = false;

    CurrentTries = 0;
    MaxTries = MAX_TRIES;

    HiddenWord = HIDDEN_WORD;
    GenerateLetterMaps(HiddenWord);
}


void FBullCowGame::GenerateLetterMaps(FString Word) {
    TMap<char, int> WordMap;

    for (int32 i = 0; i < Word.length(); i++) {
        LetterExistenceMap[Word[i]] = true;
        LetterPositionMap[Word[i]] = i;
    }
}


EGuessValidity FBullCowGame::GetGuessValidity(FString Guess) const {
    if (Guess.length() != GetHiddenWordLength())
        return EGuessValidity::INVALID_LENGTH;
    else if (!IsIsogram(Guess))
        return EGuessValidity::NOT_ISOGRAM;

    return EGuessValidity::OK;
}


bool FBullCowGame::IsIsogram(FString Word) const {
    TMap<char, bool> IsoMap;

    for (char Letter : Word) {
        if (IsoMap[Letter])
            return false;
        else
            IsoMap[Letter] = true;
    }

    return true;
}


FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
    FBullCowCount BCCount;

    CurrentTries++;

    for (int32 i = 0; i < Guess.length(); i++) {
        if (LetterExistenceMap[Guess[i]]) {
            if (LetterPositionMap[Guess[i]] == i)
                BCCount.NumBulls++;
            else
                BCCount.NumCows++;
        }
    }

    if (BCCount.NumBulls == GetHiddenWordLength())
        bGameWon = true;

    return BCCount;
}
