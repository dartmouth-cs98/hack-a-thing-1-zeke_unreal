// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBullCowCartridge, Log, All);

struct FBullAndCowCounts {
    int32 Bulls = 0;
    int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
    GENERATED_BODY()

    public:
    virtual void BeginPlay() override;
    virtual void OnInput(const FString& Input) override;

    // Your declarations go below!
    private:
    void AssignHiddenWord();
    void NewGame();
    void EndGame(const bool bWon);
    bool IsValidGuess(const FString &Guess);
    bool IsIsogram(const FString &Word) const;
    // I'm leaving this in here as a reference of what out parameters look like
    // void CountBullsAndCows(const FString &Guess, int32 &BullCount, int32 &CowCount) const;
    FBullAndCowCounts CountBullsAndCows(const FString &Guess) const;
    TArray<FString> GetValidWords(const TArray<FString> &WordList) const;

    const FString EMPTY = TEXT("");
    const FString LIFE_STR = TEXT("life");
    const FString LIVES_STR = TEXT("lives");

    TArray<FString> HiddenWords;
    FString HiddenWord;
    int32 Lives;
    bool bIsFirstGame;
    bool bIsGameOver;
};
