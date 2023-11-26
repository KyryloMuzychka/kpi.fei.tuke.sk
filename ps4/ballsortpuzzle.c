#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "ballsortpuzzle.h"
#include "style.h"
#define MAX_SYMOLS 4

void generator(const int rows, const int columns, char field[rows][columns])
{
  srand((unsigned)time(0));

  char symbols[] = {'@', '+', '^', '*'};
  int empty_first = rand() % columns, empty_second, count_symbols[MAX_SYMOLS] = {0}, index;

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

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y)
{
  if (x != y)
  {
    int x_i = -1, y_i = rows - 1;

    for (int i = 0; i < rows; i++)
    {
      if (field[i][x] != ' ')
      {
        // printf("\n(x): %c", field[i][x]);
        x_i = i;
        break;
      }
    }

    //printf("x_i=%i", x_i);

    if (x_i != -1) // not empty column from getting element
    {
      for (int i = 0; i < rows; i++)
      {
        if (field[i][y] != ' ')
        {
          // printf("\n(y): %c", field[i][y]);
          y_i = i;
          break;
        }
      }

      //printf("y_i=%i", y_i);

      if (y_i == rows - 1)
      {
        field[y_i][y] = field[x_i][x];
        field[x_i][x] = ' ';
      }
      else if (y_i - 1 >= 0)
      {
        if (field[x_i][x] == field[y_i][y])
        {
          field[y_i - 1][y] = field[x_i][x];
          field[x_i][x] = ' ';
        }
        else
        {
          printf("MUST BE SAME");
        }
      }
    }
  }
}

bool check(const int rows, const int columns, char field[rows][columns])
{
  if (rows <= 1)
  {
    return true;
  }

  for (int i = 0; i < columns; i++)
  {
    for (int j = 1; j < rows; j++)
    {
      if (field[j][i] != field[j - 1][i])
        return false;
    }
  }

  return true;
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