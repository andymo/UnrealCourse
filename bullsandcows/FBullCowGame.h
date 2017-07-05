#include <string>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;


struct FBullCowCount {
    int32 NumCows = 0;
    int32 NumBulls = 0;
};


enum class EGuessValidity {
    OK,
    NOT_ISOGRAM,
    INVALID_LENGTH
};


class FBullCowGame {
public:
    FBullCowGame();

    int32 GetMaxTries () const;
    int32 GetCurrentTries () const;
    int32 GetHiddenWordLength() const;
    EGuessValidity GetGuessValidity(FString) const;
    bool IsGameWon() const;

    void Reset();

    void IncrementTries();

    FBullCowCount SubmitGuess(FString);

private:
    bool bGameWon;
    int32 CurrentTries;
    int32 MaxTries;
    FString HiddenWord;
    TMap<char, bool> LetterExistenceMap;
    TMap<char, int> LetterPositionMap;

    void GenerateLetterMaps(FString);
    bool IsIsogram(FString) const;
};