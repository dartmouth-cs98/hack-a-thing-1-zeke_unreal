// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::AssignHiddenWord() {
    HiddenWord = TEXT("abcde");
}

void UBullCowCartridge::NewGame() {
    Lives = WordSize;

    if (bIsFirstGame)
        PrintLine(FString::Printf(TEXT("Welcome to the Bulls & Cows Game!\n"
        "I will think of a %d letter isogram\n"
        "(a word with no repeating letters), and\n"
        "you will have %d tries to guess it. After\n"
        "each guess, I will tell you how many bulls\n"
        "and cows that answer is worth. A bull rep-\n"
        "resents a letter in my word in the correct\n"
        "spot. A cow represents a letter in my word\n"
        "in the incorrect spot. Good luck!"), WordSize, Lives));
    else
        PrintLine(FString::Printf(TEXT("I'm thinking of a %d letter isogram.\n"
        "You have %d lives. Good luck!"), WordSize, Lives));

    AssignHiddenWord();
}

void UBullCowCartridge::EndGame(const bool bWon) {
    if (bWon) {
        PrintLine(TEXT("You win!"));
    } else {
        PrintLine(TEXT("You Lose! My word was \"%s\"."), *HiddenWord);
    }

    // TODO: Play again prompt, setting bIsWaitingForPlayAgainAnswer to true

    bIsFirstGame = false;
    NewGame();
}

// When the game starts
void UBullCowCartridge::BeginPlay() {
    Super::BeginPlay();
    bIsFirstGame = true;
    NewGame();
}

// When the player hits enter
void UBullCowCartridge::OnInput(const FString& Input) {
    ClearScreen();

    /*
     *  if bIsWaitingForPlayAgainAnswer
     *      if input == yes
     *          NewGame(false)
     *      else
     *          Quit
     */

    PrintLine(TEXT("input: %s, len: %d"), *Input, Input.Len());

    if (Input.Len() != WordSize) {
        FString UpdateMessage = FString::Printf(TEXT("Remember: the word is %d characters long."), WordSize);
        
        if (!bIsFirstGame) {
            Lives--;

            if (Lives == 0) {
                PrintLine(UpdateMessage);
                EndGame(false);
            }
        }

        FString LifeStr = TEXT("life");
        FString LivesStr = TEXT("lives");
        PrintLine(TEXT("%s\nYou have %d %s remaining. Try Again!"), *UpdateMessage, Lives, (Lives == 1) ? *LifeStr : *LivesStr);

        return;
    }
    /*
     *  Check player Input
     *  if invalid,
     *      describe why it's invalid
     *      if not first game
     *          deduct life
     *          if lives == 0
     *              Lose
     *      inform how many lives remaining
     *      return
     *  else
     *      proceed to everything below
     */

    int32 CowCount = 0;
    int32 BullCount = 0;

    // count bulls and cows

    if (BullCount == WordSize) {
        EndGame(true);
    } else {
        Lives--;

        FString SChar = TEXT("s");

        if (Lives > 0) {
            PrintLine(TEXT(
                "\"%s\" is worth %d bull%s and %d cow%s.\n"
                "You have %d remaining."), *Input,
                BullCount, (BullCount == 1) ? *EMPTY : *SChar,
                CowCount, (CowCount == 1) ? *EMPTY : *SChar, Lives);
            // PrintLine(TEXT("\"[input]\" is worth [BullCount] bull(s) and [CowCount] cow(s).\n"
            // "You have [lives] remaining."));
        } else {
            EndGame(false);
        }
    }
}