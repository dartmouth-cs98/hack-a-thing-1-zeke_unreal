// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBullCowCartridge, Log, All);

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
    const bool IsIsogram(const FString &Word);
    void CountBullsAndCows(const FString &Guess, int32 &BullCount, int32 &CowCount);

    const FString EMPTY = TEXT("");
    const FString LIFE_STR = TEXT("life");
    const FString LIVES_STR = TEXT("lives");

    FString HiddenWord;
    int32 Lives;
    bool bIsFirstGame;
    bool bIsGameOver;
};
