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
    if (ValidWords.Num() == 0)
    {
        ValidWords = GetValidWords(WordList_TOP1000);
    }
    // PrintLine(TEXT("The number of valid words is %i"), ValidWords.Num());
    // Set HiddenWord
    HiddenWord = ValidWords[FMath::RandRange(0, ValidWords.Num() - 1)];
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);
    //Set Lives
    Lives = HiddenWord.Len();
    bGameOver = false;
    //Print welcome message
    PrintLine(TEXT("Welcome to our Bull Cows!"));
    //Print hind for player to guess
    PrintLine(FString::Printf(TEXT("Guess the %d letters word!"), HiddenWord.Len()));
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess.\nPress enter to continue..."));

    // TArray<FString> ValidWords;
    // PrintLine(TEXT("The number of poosible words is %i"), WordList.Num());
    // for (int32 i = 0; i < 10; i++)
    // {
    //     if (WordList[i].Len() >= 4 && WordList[i].Len() <= 8)
    //     {
    //         // PrintLine(WordList[i]);
    //         ValidWords.Emplace(WordList[i]);
    //     }
    // }
    // for (int32 Index = 0; Index < ValidWords.Num(); Index++)
    // {
    //     PrintLine(TEXT("%s."), *ValidWords[Index]);
    // }
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
        bool IsGuessIsogram = true;
        // check if isogram
        if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("Not a Isogram!"));
            IsGuessIsogram = false;
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
            if (IsGuessIsogram)
            {
                // int32 Bulls, Cows;
                // GetBullCows(Guess, Bulls, Cows);
                FBullCowCount BullCowCount = GetBullCows(Guess);
                // PrintLine(TEXT("You have %i Bulls and %i Cows"), Bulls, Cows);
                PrintLine(TEXT("You have %i Bulls and %i Cows"), BullCowCount.Bulls, BullCowCount.Cows);
            }

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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList)
{
    TArray<FString> ValidWords;
    // for (int32 Index = 0; Index < WordList.Num(); Index++)
    // {
    //     if (WordList[Index].Len() >= 4 && WordList[Index].Len() <= 8)
    //         if (IsIsogram(WordList[Index]))
    //         {
    //             ValidWords.Emplace(WordList[Index]);
    //         }
    // }
    for(FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8)
            if (IsIsogram(Word))
            {
                ValidWords.Emplace(Word);
            }
    }
    return ValidWords;
}

// void UBullCowCartridge::GetBullCows(const FString &Guess, int32 &BullCount, int32 &CowCount) const
FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    // BullCount = CowCount = 0;
    FBullCowCount BullCowCount;
    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (GuessIndex < HiddenWord.Len() && HiddenWord[GuessIndex] == Guess[GuessIndex])
        {
            // BullCount++;
            BullCowCount.Bulls++;
        }
        else
        {
            for (int32 HiddenIndex2 = 0; HiddenIndex2 < HiddenWord.Len(); HiddenIndex2++)
            {
                if (GuessIndex != HiddenIndex2)
                {
                    if (Guess[GuessIndex] == HiddenWord[HiddenIndex2])
                    {
                        // CowCount++;
                        BullCowCount.Cows++;
                        break;
                    }
                }
            }
        }
    }
    return BullCowCount;
}

