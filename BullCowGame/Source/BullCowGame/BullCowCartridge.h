// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

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

    const FString EMPTY = TEXT("");
    // const FString INTRODUCTION = TEXT("Welcome to the Bulls & Cows Game!\n"
    //     "I will think of a %d letter isogram\n"
    //     "(a word with no repeating letters), and\n"
    //     "you will have %d tries to guess it. After\n"
    //     "each guess, I will tell you how many bulls\n"
    //     "and cows that answer is worth. A bull rep-\n"
    //     "resents a letter in my word in the correct\n"
    //     "spot. A cow represents a letter in my word\n"
    //     "in the incorrect spot. Good luck!");
    // const FString NEW_GAME = TEXT("I'm thinking of a %d letter isogram.\n"
    //     "You have %d lives. Good luck!");

    FString HiddenWord;
    int32 WordSize = 5;
    int32 Lives;
    bool bIsFirstGame;
};
