// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

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
        // If guess correct
        if (Input.Len() == HiddenWord.Len() && Input == HiddenWord)
        {
            // Print Won and ask if play again
            PrintLine(TEXT("You have won!"));
            EndGame();
        }
        // If guess wrong
        else
        {
            if (Input.Len() != HiddenWord.Len())
            {
                PrintLine(FString::Printf(TEXT("The Hidden Word is %d length."), HiddenWord.Len()));
            }
            --Lives;
            // If still have lives, Lives>0
            if (Lives > 0)
            {
                // Print bulls and cows
                PrintLine(TEXT("You lost a life.\nYou have %i lives left."), Lives);
            }
            else
            {
                // Else If no lives
                // Print lose and ask if play again
                PrintLine(TEXT("You die!"));
                EndGame();
            }
        }
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