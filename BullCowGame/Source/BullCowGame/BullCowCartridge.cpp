// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

DEFINE_LOG_CATEGORY(LogBullCowCartridge);

void UBullCowCartridge::AssignHiddenWord() {
    HiddenWord = TEXT("ABCDE");
}

void UBullCowCartridge::NewGame() {
    AssignHiddenWord();
    bIsGameOver = false;
    Lives = HiddenWord.Len();

    if (bIsFirstGame)
        PrintLine(FString::Printf(TEXT("Welcome to the Bulls & Cows Game!\n"
        "I will think of a %d letter isogram\n"
        "(a word with no repeating letters), and\n"
        "you will have %d tries to guess it. After\n"
        "each guess, I will tell you how many bulls\n"
        "and cows that answer is worth. A bull rep-\n"
        "resents a letter in my word in the correct\n"
        "spot. A cow represents a letter in my word\n"
        "in the incorrect spot. Good luck!"), HiddenWord.Len(), Lives));
    else
        PrintLine(FString::Printf(TEXT("I'm thinking of a %d letter isogram.\n"
        "You have %d lives. Good luck!"), HiddenWord.Len(), Lives));
}

void UBullCowCartridge::EndGame(const bool bWon) {
    if (bWon) {
        PrintLine(TEXT("You win!"));
    } else {
        PrintLine(TEXT("You Lose! My word was \"%s\"."), *HiddenWord);
    }

    // TODO: Play again prompt, setting bIsWaitingForPlayAgainAnswer to true

    bIsFirstGame = false;
    bIsGameOver = true;

    PrintLine(TEXT("Press enter to continue."));
}

bool UBullCowCartridge::IsValidGuess(const FString &Guess) {
    /*
     * The tutorial checks if the Guess is the HiddenWord before doing any validity checks,
     * stating that time is wasted otherwise doing heavy lifting if it turns out the guess
     * is correct, but since the words are so small (my assumption is < 13 letters), the run
     * time difference would be so miniscule that it's not worth doing an extra string
     * equivalence check in the beginning. I acknowledge that the principle is solid and
     * definitely worthwhile in the cases of large computations.
     */

    bool bIsValidGuess = true;
    FString InvalidityMessage = TEXT("");

    if (Guess.Len() != HiddenWord.Len()) {
        UE_LOG(LogBullCowCartridge, Log, TEXT("Improper length: %s, %s"), *Guess, *HiddenWord);
        InvalidityMessage = FString::Printf(TEXT("Remember: the word is %d characters long."), HiddenWord.Len());
        bIsValidGuess = false;
    } else if (!IsIsogram(Guess)) {
        UE_LOG(LogBullCowCartridge, Log, TEXT("Not an isogram: %s"), *Guess);
        InvalidityMessage = TEXT("Remember: the word is an isogram (it has\nno repeating letters).");
        bIsValidGuess = false;
    }

    if (!bIsValidGuess) {
        UE_LOG(LogBullCowCartridge, Log, TEXT("Not a valid guess: %s"), *Guess);
        PrintLine(InvalidityMessage);

        if (!bIsFirstGame && --Lives == 0)
            EndGame(false);
        else {
            PrintLine(TEXT("You have %d %s remaining. Try Again!"), Lives, (Lives == 1) ? *LIFE_STR : *LIVES_STR);
        }
    }

    return bIsValidGuess;
}

const bool UBullCowCartridge::IsIsogram(const FString &Word) {
    for (int32 Char1 = 0; Char1 < Word.Len() - 1; Char1++) {
        for (int32 Char2 = Char1 + 1; Char2 < Word.Len(); Char2++) {
            if (Word[Char1] == Word[Char2]) {
                return false;
            }
        }
    }

    return true;
}

void UBullCowCartridge::CountBullsAndCows(const FString &Guess, int32 &BullCount, int32 &CowCount) {
    BullCount = 0;
    CowCount = 0;

    for (int32 HWChar = 0; HWChar < HiddenWord.Len(); HWChar++) {
        if (HiddenWord[HWChar] == Guess[HWChar])
            BullCount++;
        else
            for (int32 GChar = 0; GChar < Guess.Len(); GChar++)
                if (HiddenWord[HWChar] == Guess[GChar])
                    CowCount++;
    }
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

    if (bIsGameOver) {
        NewGame();
        return;
    }

    if (IsValidGuess(Input)) {
        int32 CowCount;
        int32 BullCount;
        CountBullsAndCows(Input.ToUpper(), BullCount, CowCount);

        if (BullCount == HiddenWord.Len()) {
            EndGame(true);
        } else {
            FString SChar = TEXT("s");

            if (--Lives > 0) {
                PrintLine(TEXT(
                    "\"%s\" is worth %d bull%s and %d cow%s.\n"
                    "You have %d %s remaining."), *(Input.ToUpper()),
                    BullCount, (BullCount == 1) ? *EMPTY : *SChar,
                    CowCount, (CowCount == 1) ? *EMPTY : *SChar,
                    Lives, (Lives == 1) ? *LIFE_STR : *LIVES_STR);
                // PrintLine(TEXT("\"[input]\" is worth [BullCount] bull(s) and [CowCount] cow(s).\n"
                // "You have [lives] remaining."));
            } else {
                EndGame(false);
            }
        }
    }
}