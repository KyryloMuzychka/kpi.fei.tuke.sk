#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ballsortpuzzle.h"

#include "c4.h"

#include "style.h"

int main()
{
  char field[4][4];
  initialize_board(4,4,field);
  print_board(4,4,field);
  
  //game_field(4,4,field);
  ball_sort_puzzle();
  //initialize_board(4,4,field);
  
  return 0;
}
