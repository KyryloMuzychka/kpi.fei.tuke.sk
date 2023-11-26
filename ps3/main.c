#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include "hangman.h"
#include "morse.h"
#define MAX 15

int main()
{
    char available_alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    get_available_letters("ABCDEFGHIJKLMNOPQRSTUVWXYZ", available_alphabet);
    printf("av: %s\n", available_alphabet);

     char a[] = "abcdefghijklmnopqrstuvwxyz";
    get_available_letters("abcd", a);
    printf("av: %s\n", a);



//abcdefghijklmnopqrstuvwxyz


    char b[]  = "abcdefghijklmnopqrstuvwxyz";
    get_available_letters("arpstxgoieyu", b);
    // result = "bcdfhjklmnqvwz"
    printf("av: %s\n", b);


    char word[MAX];// = "hello"; // here funtion from server
    //char word[] = "hello"; // here funtion from server
    get_word(word);
    hangman(word);   

      // task 5
    char output5[150];
    text_to_morse("Hello", output5); //prints: .... . .-.. .-.. ---
    puts(output5);

    // task 6
    char output6[150];
    morse_to_text(".... . .-.. .-.. --- -----", output6);
    printf("%s\n", output6); // prints: HELLO

    // task 7
    if (is_morse_code_valid(".... . .-.. .-.. ---"))
    {
        printf("Code is valid! \n");
    }
    else
    {
        printf("Code is invalid! \n");
    }
    // prints: Code is valid!

    if (is_morse_code_valid(".... . .-.--. .-.. ---"))
    {
        printf("Code is valid! \n");
    }
    else
    {
        printf("Code is invalid! \n");
    }
    // prints: Code is invalid!

    return 0;
}