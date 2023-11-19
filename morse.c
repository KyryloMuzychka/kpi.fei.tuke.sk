#include <stdio.h>
#include <string.h>

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



int main()
{
	char output[150];

	text_to_morse("Hello", output);
	puts(output);


	//prints: .... . .-.. .-.. ---
	return 0;
}