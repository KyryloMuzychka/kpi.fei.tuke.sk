#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

void Fill(char output[], int *index, const char morse[])
{
    for (int i = 0; i < strlen(morse); i++)
    {
        output[(*index)++] = morse[i];
    }
}

void AddSymbol(char symbol[], const char *morseCodes[], int size, char output[], int *resultIndex, int adding)
{
    for (int j = 0; j < size; j++)
    {
        if (strcmp(symbol, morseCodes[j]) == 0)
        {
            output[(*resultIndex)++] = (char)(j + adding);
            break;
        }
    }
}

int CheckSymbol(char symbol[], const char *morseCodes[], int size)
{
    for (int j = 0; j < size; j++)
        if (strcmp(symbol, morseCodes[j]) == 0)
            return 1;
    return 0;
}

void text_to_morse(const char text[], char output[])
{
    const char *morseCodesLetters[] = {
        ".-", "-...", "-.-.", "-..", ".",     // A-E
        "..-.", "--.", "....", "..", ".---",  // F-J
        "-.-", ".-..", "--", "-.", "---",     // K-O
        ".--.", "--.-", ".-.", "...", "-",    // P-T
        "..-", "...-", ".--", "-..-", "-.--", // U-Y
        "--.."                                // Z
    };

    const char *morseCodesDigits[] = {
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

    int index = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if ((int)toupper(text[i]) >= 65 && (int)toupper(text[i]) <= 90)
        {
            Fill(output, &index, morseCodesLetters[(int)toupper(text[i]) - 65]);
        }
        else if (text[i] >= 48 && text[i] <= 57)
        {
            Fill(output, &index, morseCodesDigits[(int)text[i] - 48]);
        }
        output[index++] = ' ';
    }
    if (index >= 1)
        output[index - 1] = '\0';
}

void morse_to_text(const char morse[], char output[])
{
    const char *morseCodesLetters[] = {
        ".-", "-...", "-.-.", "-..", ".",     // A-E
        "..-.", "--.", "....", "..", ".---",  // F-J
        "-.-", ".-..", "--", "-.", "---",     // K-O
        ".--.", "--.-", ".-.", "...", "-",    // P-T
        "..-", "...-", ".--", "-..-", "-.--", // U-Y
        "--.."                                // Z
    };

    const char *morseCodesDigits[] = {
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

    char symbol[MAX];
    int index = 0, resultIndex = 0;

    for (int i = 0; i < strlen(morse); i++)
    {
        if (morse[i] != ' ')
        {
            symbol[index++] = morse[i];
        }
        else
        {
            symbol[index] = '\0';
            index = 0;
            AddSymbol(symbol, morseCodesLetters, sizeof(morseCodesLetters) / sizeof(morseCodesLetters[0]), output, &resultIndex, 65);
            AddSymbol(symbol, morseCodesDigits, sizeof(morseCodesDigits) / sizeof(morseCodesDigits[0]), output, &resultIndex, 48);
        }
    }

    if (index > 0)
    {
        symbol[index] = '\0';
        AddSymbol(symbol, morseCodesLetters, sizeof(morseCodesLetters) / sizeof(morseCodesLetters[0]), output, &resultIndex, 65);
        AddSymbol(symbol, morseCodesDigits, sizeof(morseCodesDigits) / sizeof(morseCodesDigits[0]), output, &resultIndex, 48);
    }

    output[resultIndex] = '\0';
}

int is_morse_code_valid(const char morse[])
{
    const char *morseCodesLetters[] = {
        ".-", "-...", "-.-.", "-..", ".",     // A-E
        "..-.", "--.", "....", "..", ".---",  // F-J
        "-.-", ".-..", "--", "-.", "---",     // K-O
        ".--.", "--.-", ".-.", "...", "-",    // P-T
        "..-", "...-", ".--", "-..-", "-.--", // U-Y
        "--.."                                // Z
    };

    const char *morseCodesDigits[] = {
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

    char symbol[MAX];
    int index = 0, valid = 1; // resultIndex = 0;

    for (int i = 0; i < strlen(morse); i++)
    {
        if (!valid)
            return 0;

        if (morse[i] != ' ')
        {
            symbol[index++] = morse[i];
        }
        else
        {
            valid = 0;
            symbol[index] = '\0';
            index = 0;

            valid = CheckSymbol(symbol, morseCodesLetters, sizeof(morseCodesLetters) / sizeof(morseCodesLetters[0]));
            if (!valid)
                valid = CheckSymbol(symbol, morseCodesDigits, sizeof(morseCodesDigits) / sizeof(morseCodesDigits[0]));
        }
    }

    if (index > 0)
    {
        valid = 0;
        symbol[index] = '\0';
        valid = CheckSymbol(symbol, morseCodesLetters, sizeof(morseCodesLetters) / sizeof(morseCodesLetters[0]));
        if (!valid)
            valid = CheckSymbol(symbol, morseCodesDigits, sizeof(morseCodesDigits) / sizeof(morseCodesDigits[0]));
    }

    return valid;
}
