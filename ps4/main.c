#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ballsortpuzzle.h"
#include "c4.h"
#include "style.h"

#define C4_MAX_ROWS 7
#define C4_MAX_COLS 6

void connect_four()
{
  char player = 'X', board[C4_MAX_ROWS][C4_MAX_COLS];
  initialize_board(C4_MAX_ROWS, C4_MAX_COLS, board);
  print_board(C4_MAX_ROWS, C4_MAX_COLS, board);
  int move;
  do {
    if (player == 'X')
    {
      printf("Player 1, enter your move (1-%i): ", C4_MAX_COLS);
    }
    else
    {
      printf("Player 2, enter your move (1-%i): ", C4_MAX_COLS);
    }
    scanf(" %i", &move);
    move--;
    if (is_valid_move(C4_MAX_ROWS, C4_MAX_COLS, board, move) && drop_piece(C4_MAX_ROWS, C4_MAX_COLS, board, move, player))
    {
      int row_ = 0;
      if (board[C4_MAX_ROWS-1][move] == '.')
        row_ = C4_MAX_ROWS-1;
      while (board[row_++][move] == '.');     
      row_--; 
      if (check_win(C4_MAX_ROWS, C4_MAX_COLS, board, row_, move, player))
      {
        printf("Player %d wins!\n", (player == 'X') ? 1 : 2);
        break;
      }        
      player = (player == 'X') ? 'O' : 'X';  
      print_board(C4_MAX_ROWS, C4_MAX_COLS, board);
    }        
  } while (!is_board_full(C4_MAX_ROWS, C4_MAX_COLS, board));
  if (!is_board_full(C4_MAX_ROWS, C4_MAX_COLS, board))
  {
    printf("It's a draw!\n");
  }
}

int main()
{
  connect_four();
  ball_sort_puzzle();  
  return 0;
}
