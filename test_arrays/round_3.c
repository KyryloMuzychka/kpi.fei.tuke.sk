#include <stdio.h>
#include <ctype.h>
#include <string.h>

int max_2d(const int size, int array[][size])
{
  if (array == NULL)  
    return -1;      
  
  int max = array[0][0];

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)    
      if (array[i][j] > max)
        max = array[i][j];

  return max;
}

int vowels_count_2d(const int rows, const int cols, char strings[][cols])
{
  if (strings == NULL)
    return -1;

  int count = 0;
  
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)    
      if (tolower(strings[i][j]) == 'a' || tolower(strings[i][j]) == 'e' || tolower(strings[i][j]) == 'i' || tolower(strings[i][j]) == 'o' || tolower(strings[i][j]) == 'u')
        count++;    

  return count;  
}

int is_in_array_2d(const int num, const int size, int array[][size])
{
  if (array == NULL)
    return -1;

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)    
      if (array[i][j] == num)
        return 1;

  return 0;
}

int main()
{
  int array[2][2] = {{1,2}, {0,-3} };
  printf("%d\n", max_2d(2, array)); // 2

  char strings[3][50] = {"hello WORLD!", "aHOJ", "Ahoj"};
  printf("%d\n", vowels_count_2d(3, 50, strings)); // 7
  
  int array1[2][2] = { {1,0}, {0,-3} };
  printf("%d %d\n", is_in_array_2d(2, 2, array1), is_in_array_2d(-3, 2, array1) ); // 0 1

  return 0;
}