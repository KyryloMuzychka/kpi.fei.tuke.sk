#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "ballsortpuzzle.h"
#include "style.h"
#define MAX_SYMOLS 4
#define MAX_ROWS 4
#define MAX_COLUMNS 6

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
    int x_i = -1, y_i = - 1;

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
          //printf("\n\ny_i====%i\n\n", y_i);
          break;
        }
      }

      //printf("y_i=%i", y_i);

      if (y_i == - 1)
      {
        field[rows-1][y] = field[x_i][x];
        field[x_i][x] = ' ';
      }
      else if (y_i - 1 >= 0)
      {
        if (field[x_i][x] == field[y_i][y])
        {
          //printf("\n2)y_i======%i\n",y_i);
          field[y_i - 1][y] = field[x_i][x];
          field[x_i][x] = ' ';
        }
        else
        {
          printf("MUST BE SAME\n");
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
  printf("\n");
}

void ball_sort_puzzle()
{
  int what, where;
  char field[MAX_ROWS][MAX_COLUMNS];
  generator(4, 6, field);

  do {
    //system("cls");
    
    game_field(MAX_ROWS, MAX_COLUMNS, field);
    
    printf(ANSI_COLOR_CYAN);

    printf("Enter what: ");
    scanf("%i", &what);
    
    printf("Enter where: ");
    scanf("%i", &where);
    
    printf(ANSI_COLOR_RESET);

    down_possible(MAX_ROWS, MAX_COLUMNS, field, what-1, where-1);
 
  } while (!check(MAX_ROWS, MAX_COLUMNS, field));
  game_field(MAX_ROWS, MAX_COLUMNS, field);
  printf(ANSI_BOLD ANSI_COLOR_MAGENTA "Congratulations! You won!" ANSI_COLOR_RESET);  
}