#include <stdio.h>
#include "c4.h"
#include "style.h"

void initialize_board(int rows, int cols, char board[rows][cols])
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      board[i][j] = '.';
    }
  }
}

void print_line(int cols)
{
  printf("  ");
  for (int j = 0; j < cols; j++)
  {
    printf("----");
  }
  printf("-\n");
}

void print_board(int rows, int cols, const char board[rows][cols])
{
  printf(ANSI_COLOR_GREEN ANSI_BOLD);

  print_line(cols);

  for (int i = 0; i < rows; i++)
  {
    printf(ANSI_COLOR_CYAN "%i ", i + 1);
    printf(ANSI_COLOR_GREEN);
    for (int j = 0; j < cols; j++)
    {
      if (j == 0)
        printf("|");

      if (board[i][j] == '.')
        printf(ANSI_COLOR_BLUE);
      else if (board[i][j] == 'X')
        printf(ANSI_COLOR_MAGENTA);
      else if (board[i][j] == 'O')
        printf(ANSI_COLOR_YELLOW);

      printf(" %c ", board[i][j]);
      printf(ANSI_COLOR_GREEN "|");
    }
    printf("\n");

    print_line(cols);
  }
  printf(ANSI_COLOR_CYAN);
  printf("   ");
  for (int i = 0; i < cols; i++)
  {
    printf(" %i  ", i + 1);
  }
  printf(ANSI_COLOR_RESET "\n");
}

int is_valid_move(int rows, int cols, const char board[rows][cols], int col)
{
  if (col >= cols || col < 0)
    return 0;
  return (board[0][col] == '.') ? 1 : 0;
}

int drop_piece(int rows, int cols, char board[rows][cols], int col, char player_piece)
{
  if (board[rows - 1][col] == '.')
  {
    board[rows - 1][col] = player_piece;
    return 1;
  }
  else
  {
    for (int i = 0; i < rows; i++)
    {
      if (board[i][col] != '.' && i != 0)
      {
        board[i - 1][col] = player_piece;
        return 1;
      }
    }
  }
  return 0;
}


