#include <stdio.h>

#include <string.h>

#include <ctype.h>

#define MAX 500
int main()
{
  FILE *file = fopen("bananas1.txt", "r");
  char find[]={"ananas"};
  int size = sizeof(find)/sizeof(find[0])-1, index = 0, count = 0;

  do
    {
        // Taking input single character at a time
        char c = fgetc(file);

        if (tolower(c) == find[index] && index != size-1)
        {
          index++;
        }
        else if (index == size-1)
        {
          count++;
          index = 0;
        }
        else 
        {
          index=0;
        }

        //printf("%c", c);
    }  while(!feof(file));

  //printf("count = %i", count);

  fclose(file);

  file = fopen("bananas1.txt", "w");

  // fputc(count + '0', file);
  // count = 90;

  fprintf(file, "%d\n", count);

  fclose(file);

  return 0;
}