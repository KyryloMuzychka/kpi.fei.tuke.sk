#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ballsortpuzzle.h"
#include "style.h"
#define MAX_SYMOLS 4

int main()
{
  char field[4][6];
  generator(4, 6, field);
  game_field(4, 6, field);  
  return 0;
}
