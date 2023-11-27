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
  printf("\n\n%i\n\n", is_valid_move(4,4,field,0));
  ball_sort_puzzle();  
  return 0;
}
