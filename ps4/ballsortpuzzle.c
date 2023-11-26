#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ballsortpuzzle.h"
#include "style.h"
#define MAX_SYMOLS 4

void generator(const int rows, const int columns, char field[rows][columns])
{
  srand((unsigned)time(0));

  char symbols[] = {'@', '+', '^', '*'}, symbol;
  int empty_first = rand() % columns, empty_second, count_symbols[MAX_SYMOLS] = {0}, count = 0, index;

  do
  {
    empty_second = rand() % columns;
  } while (empty_first == empty_second);

  // printf("%i, %i\n", empty_first, empty_second);

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      if (j == empty_first || j == empty_second)
      {
        field[i][j] = BLANK;
      }
      else
      {
        do
        {
          index = rand() % MAX_SYMOLS;
        } while (count_symbols[index] >= rows);

        count_symbols[index]++;
        field[i][j] = symbols[index];
      }
    }
  }
}

void game_field(const int rows, const int columns, char field[rows][columns])
{
  // printf(ANSI_BOLD ANSI_COLOR_RED "Этот текст красный и жирный\n" ANSI_COLOR_RESET);
  // printf(ANSI_BOLD ANSI_COLOR_GREEN "Этот текст зелёный и жирный\n" ANSI_COLOR_RESET);
  // printf(ANSI_BOLD ANSI_COLOR_YELLOW "Этот текст жёлтый и жирный\n" ANSI_COLOR_RESET);
  // printf(ANSI_BOLD ANSI_COLOR_BLUE "Этот текст синий и жирный\n" ANSI_COLOR_RESET);
  // printf(ANSI_BOLD ANSI_COLOR_MAGENTA "Этот текст пурпурный и жирный\n" ANSI_COLOR_RESET);
  // printf(ANSI_BOLD ANSI_COLOR_CYAN "Этот текст голубой и жирный\n" ANSI_COLOR_RESET);

  for (int i = 0; i < rows; i++)
  {
    printf(ANSI_BOLD ANSI_COLOR_CYAN " %i " ANSI_COLOR_RESET, i + 1);

    for (int j = 0; j < columns; j++)
    {
      printf(ANSI_BOLD ANSI_COLOR_BLUE " | " ANSI_COLOR_RESET);
      if (field[i][j] == '@')
      {
        printf(ANSI_BOLD ANSI_COLOR_MAGENTA "%c" ANSI_COLOR_RESET, field[i][j]);
      }
      else if (field[i][j] == '*')
      {
        printf(ANSI_BOLD ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, field[i][j]);
      }
      else if (field[i][j] == '+')
      {
        printf(ANSI_BOLD ANSI_COLOR_YELLOW "%c" ANSI_COLOR_RESET, field[i][j]);
      }
      else if (field[i][j] == '^')
      {
        printf(ANSI_BOLD ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, field[i][j]);
      }
      else
        printf("%c", field[i][j]);
      printf(ANSI_BOLD ANSI_COLOR_BLUE " | " ANSI_COLOR_RESET);
    }
    printf("\n");
  }
  printf("   ");
  for (int j = 0; j < columns; j++)
  {
    printf(ANSI_BOLD ANSI_COLOR_BLUE "  ---  " ANSI_BOLD ANSI_COLOR_BLUE);
  }
  printf("\n");
  for (int j = 0; j < columns; j++)
  {
    printf(ANSI_BOLD ANSI_COLOR_CYAN "%7i" ANSI_COLOR_RESET, j + 1);
  }
}

int main()
{
  char field[4][6];
  generator(4, 6, field);
  game_field(4, 6, field);
  return 0;
}
