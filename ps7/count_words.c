#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 500
int main()
{
  FILE *file = fopen("bananas1.txt", "r");
  char find[] = {"ANANAS"};
  
    
  int size = sizeof(find) / sizeof(find[0]) - 1, index = 0, count = 0;
  char c;
  
  while ((c = fgetc(file)) != EOF)
  {
   
    if (((int)c == (int)find[index] || (int)c == (int)find[index] + 32) && index != size - 1)
    {
      index++;
    }
    else if (index == size - 1)
    {
      count++;
      index = 0;
    }
    else
    {
      index = 0;
    }
  }

  fclose(file);
  file = fopen("bananas1.txt", "w");  
  fputc(count + '0', file);
  fclose(file);

  return 0;
}