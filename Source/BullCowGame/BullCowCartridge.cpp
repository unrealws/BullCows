// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    //Game start here
    SetupGame();
    //Debug line
    // PrintLine(TEXT("The HiddenWord is: %s.\nIt is %i characters long."), *HiddenWord, HiddenWord.Len());
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    // ClearScreen();
    //if game is over, then resetup the game
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        // else checking the player guess
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    //Set HiddenWord
    HiddenWord = TEXT("about");
    //Set Lives
    Lives = HiddenWord.Len();
    bGameOver = false;
    //Print welcome message
    PrintLine(TEXT("Welcome to our Bull Cows!"));
    //Print hind for player to guess
    PrintLine(FString::Printf(TEXT("Guess the %d letters word!"), HiddenWord.Len()));
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess.\nPress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
{
    // If guess correct
    if (Guess.Len() == HiddenWord.Len() && Guess == HiddenWord)
    {
        // Print Won and ask if play again
        PrintLine(TEXT("Congratulations, You won!"));
        EndGame();
    }
    // If guess wrong
    else
    {
        // some hints
        // check if isogram
        if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("Not a Isogram!"));
        }

        // check if right length
        if (Guess.Len() != HiddenWord.Len())
        {
            PrintLine(FString::Printf(TEXT("The Hidden Word is %d length."), HiddenWord.Len()));
        }

        --Lives;
        // If still have lives, Lives>0
        if (Lives > 0)
        {
            // Print bulls and cows
            PrintLine(TEXT("You lost a life. %i lives left."), Lives);
        }
        else
        {
            // Else If no lives
            // Print lose and ask if play again
            PrintLine(TEXT("Sorry, You die!"));
            EndGame();
        }
    }
}

bool UBullCowCartridge::IsIsogram(const FString &Word) const
{
    int32 Len = Word.Len();
    if (Len > 0)
    {
        for (int32 i = 0; i < Len; i++)
        {
            // for (int32 j = 0; j < Len; j++) slow
            for (int32 j = i + 1; j < Len; j++)
            {
                // if (i != j && Word[j] == Word[i]) slow
                if (Word[i] == Word[j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}