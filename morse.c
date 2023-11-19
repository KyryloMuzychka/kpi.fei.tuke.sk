#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

void Fill(char output[], int* index, const char morse[])
{
    for (int i = 0; i < strlen(morse); i++)
    {
        output[(*index)++] = morse[i];
    }
}

void text_to_morse(const char text[], char output[])
{
    const char* morseCodesLetters[] = {
       ".-", "-...", "-.-.", "-..", ".",    // A-E
       "..-.", "--.", "....", "..", ".---", // F-J
       "-.-", ".-..", "--", "-.", "---",    // K-O
       ".--.", "--.-", ".-.", "...", "-",   // P-T
       "..-", "...-", ".--", "-..-", "-.--",// U-Y
       "--.."                              // Z            
    };

    const char* morseCodesDigits[] = {     
        "-----", ".----", "..---", "...--", // 0-3
        "....-", ".....", "-....", "--...", // 4-7
        "---..", "----."                    // 8-9    
    };
  
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
    output[index-1] = '\0';
}

void morse_to_text(const char morse[], char output[])
{
    const char* morseCodesLetters[] = {
       ".-", "-...", "-.-.", "-..", ".",    // A-E
       "..-.", "--.", "....", "..", ".---", // F-J
       "-.-", ".-..", "--", "-.", "---",    // K-O
       ".--.", "--.-", ".-.", "...", "-",   // P-T
       "..-", "...-", ".--", "-..-", "-.--",// U-Y
       "--.."                              // Z            
    };

    const char* morseCodesDigits[] = {     
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
    };

    char symbol[MAX];
    int index = 0, resultIndex = 0;
    for (int i = 0; i < strlen(morse); i++)
    {        
        if (morse[i] != ' ')
        {
            symbol[index++] = morse[i];
            //printf("%c",symbol[index-1]);
        }
        else
        {
            symbol[index] = '\0';
            index = 0;

            for (int j = 0; j < strlen(*morseCodesLetters); j++)
            {
                
                if (strcmp(symbol, morseCodesLetters[j]) == 0)
                {
                    output[resultIndex++] = (char)(j+65);
                }
            }

            for (int j = 0; j < strlen(*morseCodesDigits); j++)
            {
            //  printf("%s\n", morseCodesDigits[j]);

                if (strcmp(symbol, morseCodesDigits[j]) == 0)
                {
                    output[resultIndex++] = (char)(j+65);
                }
            }
            //  printf(" %s\n", symbol);
            //printf("\n");
        }                
    }

    printf("%lu", strlen(*morseCodesDigits));

        for (int j = 0; j < strlen(*morseCodesDigits); j++)
        {
            printf("%s\n", morseCodesDigits[j]);

            if (strcmp(symbol, morseCodesDigits[j]) == 0)
            {
                output[resultIndex++] = (char)(j+65);
            }
        }

    output[resultIndex] = '\0';
}



int main()
{
    // task 5
	//char output[150];
	//text_to_morse("Hello", output);
	//puts(output);

    // task 6
    char output[150];
    morse_to_text(".... . .-.. .-.. ---", output);
    printf("morse\n");
    printf("%s", output);
    //prints: HELLO
    
	//prints: .... . .-.. .-.. ---
	return 0;
}