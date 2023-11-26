#include <stdio.h>
#include <ctype.h>
#include <string.h>

int find_first_A(const char string[])
{
  if (string == NULL)
  { 
    printf("NULL ");
    return -1;    
  }
  for (int i = 0; i < strlen(string); i++)
  {
    if (tolower(string[i]) == 'a')
    {
      return i;
    }
  }
  return -1;
}

int direction_correction(const int degree)
{
  if (degree % 90 || degree < 0) 
  {
    printf("not valid");
    return -1;
  }
  if (degree >= 360)
  {
    return degree-360;
  }
  return degree;
}

int is_triangle(const int alpha, const int beta, const int gamma)
{
  if (alpha < 1 || beta < 1 || gamma < 1)
    return -1;
  return (alpha + beta + gamma == 180) ? 1 : 0;
}

int main()
{
  // tesk 1
  printf("task1\n");
  char* nullString = NULL;
  printf("%d\n", find_first_A("Tomorrow afternoon")); // 9
  printf("%d\n", find_first_A("Tomorrow fternoon")); // -1
  printf("%d\n", find_first_A(nullString)); // NULL -1
  // task 2
  printf("task2\n");
  printf("%d %d %d\n", direction_correction(-90), direction_correction(540), direction_correction(180)); // -1 180 180
  printf("%d %d %d\n", direction_correction(0), direction_correction(90), direction_correction(270)); // 0 90 270
  printf("%d %d %d\n", direction_correction(67), direction_correction(547), direction_correction(270)); // -1 -1 270
  // task 3
  printf("task3\n");
  printf("%d %d\n", is_triangle(120,30,30), is_triangle(-20,0,200)); // 1 -1
  printf("%d %d\n", is_triangle(120,30,31), is_triangle(10,0,200)); // 0 -1
  printf("%d %d\n", is_triangle(120,30,31), is_triangle(10,2,1)); // 0 0
  return 0;
}