#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 15


int is_word_guessed(const char secret[], const char letters_guessed[])
{
    int check = 0;
    for (int i = 0; i < strlen(secret); i++)
        for (int j = 0; j < strlen(letters_guessed); j++)
            if (secret[i] == letters_guessed[j])
                check++;
    return check == strlen(secret) ? 1 : 0;
}


void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[])
{
    for (int i = 0; i < strlen(secret); i++)
    {
        guessed_word[i] = '_';
        for (int j = 0; j < strlen(letters_guessed); j++)
        {
            if (secret[i] == letters_guessed[j])
            {
                guessed_word[i] = secret[i];
                break;
            }
        }
    }
    guessed_word[strlen(secret)] = '\0';
}


void get_available_letters(const char letters_guessed[], char available_letters[])
{
    int writeIndex = 0;
    for (int i = 0; i < strlen(available_letters); i++)
    {
        int isGuessed = 0;
        for (int j = 0; j < strlen(letters_guessed); j++)
        {
            if (available_letters[i] == letters_guessed[j])
            {
                isGuessed = 1;
                break;
            }
        }
        if (!isGuessed)
        {
            available_letters[writeIndex++] = available_letters[i];
        }
    }
    available_letters[writeIndex] = '\0';
}


void Welcome(const char secret[])
{
    printf("Welcome to the game, Hangman!\nI am thinking of a word that is %lu letters long.", strlen(secret));
}


void GetInformation(int attempts, const char available_letters[])
{
    printf("\n-------------\n");
    printf("You have %i guesses left.\n", attempts);
    printf("Available letters: %s", available_letters);
    printf("\nPlease guess a letter: ");
}


void QuickGuess(const char secret[], const char letters[])
{
    if (strlen(secret) !=  strlen(letters))
    {
        printf("Sorry, bad guess. The word was %s.\n", secret);
        return;        
    }
    for (int i = 0; i < strlen(secret); i++)
    {
        if (secret[i] != letters[i])
        {
            printf("Sorry, bad guess. The word was %s.\n", secret);
            return;
        }
    }
    printf("Congratulations, you won!\n");
}


void ToLowerCase(char letters[])
{
    for (int i = 0; i < strlen(letters); i++)
    {
        letters[i] = tolower(letters[i]);
    }
}


int SymbolInArray(char symbol, const char array[])
{
    return strchr(array, symbol) != NULL;
    //    for (int i = 0; i < strlen(array); i++)
    //    {
    //        if (array[i] == symbol)
    //        {
    //            return 1;
    //        }
    //    }
    //    return 0;
}


void PrintLine(void)
{
    printf("\n-------------\n");
}


void PrintWordWithSpaces(const char* word)
{
    for (int i = 0; i < strlen(word); i++)
        printf("%c ", word[i]);
}


void hangman(const char secret_word[])
{
    int attempts = 8, index = 0;
    char letter, letters[MAX], guessed_letters[MAX], word_guessed[MAX],
        available_alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    Welcome(secret_word);

    do {

        GetInformation(attempts, available_alphabet);
        
        printf("\033[1m"); // bold
        scanf(" %s", letters);
        printf("\033[0m"); // normal

        ToLowerCase(letters);

        if (strlen(letters) > 1) {
            QuickGuess(secret_word, letters);
            break;
        }
        else {
            letter = letters[0];

            get_guessed_word(secret_word, guessed_letters, word_guessed);

            if (SymbolInArray(letter, guessed_letters)) {
                printf("Oops! You've already guessed that letter: ");
                PrintWordWithSpaces(word_guessed);
            }
            else if (!SymbolInArray(letter, available_alphabet)) {
                printf("Oops! '%c' is not a valid letter: ", letter);
                PrintWordWithSpaces(word_guessed);
            }
            else if (SymbolInArray(letter, secret_word)) {
                guessed_letters[index++] = letter;
                printf("Good guess: ");
                get_guessed_word(secret_word, guessed_letters, word_guessed);
                PrintWordWithSpaces(word_guessed);
            }
            else if (!SymbolInArray(letter, secret_word)) {
                guessed_letters[index++] = letter;
                printf("Oops! That letter is not in my word: ");
                PrintWordWithSpaces(word_guessed);
                attempts--;
            }

            if (is_word_guessed(secret_word, guessed_letters)) {
                PrintLine();
                printf("Congratulations, you won!\n");
                break;
            }

            get_available_letters(guessed_letters, available_alphabet);

        }
    } while (attempts > 0);

    if (!attempts) {
        PrintLine();
        printf("Sorry, you ran out of guesses. The word was %s.\n", secret_word);
    }
}


int main()
{
    char word[] = "hello"; // here funtion from server
    hangman(word);
    return 0;
}
