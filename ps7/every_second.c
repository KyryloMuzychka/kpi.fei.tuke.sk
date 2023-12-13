#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX 500

int main()
{
  FILE *file = fopen("input.txt", "r");
  FILE *output = fopen("output.txt", "w");
  char start[] = {"START"}, result[MAX];
  char stop[] = {"STOP"}, stopSize = sizeof(stop) / sizeof(stop[0]);
  int sizeStart = sizeof(start) / sizeof(start[0]), index = 0, i = 0, index_stop = 0;
  bool write = false;

  do
  {
    char c = fgetc(file);

    if (c == start[index] && index < sizeStart)
    {
      index++;
    }
    else
    {
      index = 0;
    }

  } while (!feof(file) && !(index == sizeStart - 1));

  fgetc(file);

  while (!feof(file))
  {
    char c = fgetc(file);

    if (c == ' ')
    {
      if (!write && i != 0)
      {
        result[i++] = c;
      }
      write = !write;
    }
    else if (write)
    {
      result[i++] = c;
    }
  }

  char *stopPosition = strstr(result, stop);
  if (stopPosition != NULL)
  {
    *stopPosition = '\0';
  }

  printf("%s\n", result);

  fputs(result, output);

  fclose(file);
  fclose(output);

  return 0;
}