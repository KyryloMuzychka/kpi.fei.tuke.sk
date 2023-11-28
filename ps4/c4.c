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
  //printf("  ");
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
    //printf(ANSI_COLOR_CYAN "%i ", i + 1);
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
  //printf("   ");
  for (int i = 0; i < cols; i++)
  {
    printf("  %i ", i + 1);
  }
  printf(ANSI_COLOR_RESET "\n");
}

int is_valid_move(int rows, int cols, const char board[rows][cols], int col)
{
  col--;
  if (col >= cols || col < 0)
    return 0;
  return (board[0][col] == '.') ? 1 : 0;
}

int drop_piece(int rows, int cols, char board[rows][cols], int col, char player_piece)
{
  col--;
  if (col >= 0 && col < cols && board[0][col] == '.')
  {
    int i = rows-1;
    while (board[i--][col] != '.');
    i++;
    if (i >= 0)
    {
      board[i][col] = player_piece;
      //printf("\ni=%i\n",i);
      return i;
    }
  }
  return 0;
}

int check_win(int rows, int cols, const char board[rows][cols], int row, int col, char player_piece)
{
  int start_col = col, start_row = row;

  // check row
  int count = 1;
  for (int i = 0; i < cols - 1; ++i)
  {
    if (board[row][i] == player_piece && board[row][i] == board[row][i + 1])
    {
      count++;
      if (count == 4)
      {
        return 1;
      }
    }
    else
    {
      count = 1;
    }
  }

  // check column
  count = 1;
  for (int i = 0; i < rows - 1; ++i)
  {
    if (board[i][col] == player_piece && board[i][col] == board[i + 1][col])
    {
      count++;
      if (count == 4)
      {
        return 1;
      }
    }
    else
    {
      count = 1;
    }
  }

  /* check diagonal (main) "\" */
  count = 1;
  while (col > 0 && row > 0)
  {
    col--;
    row--;
  }

  while (row < rows - 1 && col < cols - 1)
  {
    if (board[row][col] == player_piece && board[row][col] == board[row + 1][col + 1])
    {
      count++;
      if (count == 4)
      {
        return 1;
      }
    }
    else
    {
      count = 1;
    }
    row++;
    col++;
  }

  /* check diagonal "/" */
  count = 1;
  col = start_col; row = start_row;
  while (col < cols && row > 0)
  {
    col++;
    row--;
  }


  while (row < rows - 1 && col > 0)
  {
    if (board[row][col] == player_piece && board[row][col] == board[row + 1][col - 1])
    {
      count++;
      if (count == 4)
      {
        return 1;
      }
    }
    else
    {
      count = 1;
    }
    row++;
    col--;
  }




  return 0;
}

int is_board_full(int rows, int cols, const char board[rows][cols])
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (board[i][j] == '.')
        return 0;
    }
  }
  return 1;
}