#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

void reverse_array(bool arr[], int size)
{
  int start = 0;
  int end = size - 1;

  while (start < end)
  {
    bool temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;

    start++;
    end--;
  }
}

void encode_char(const char character, bool bits[8])
{
  int original = (int)character, i = 0;
  while (original)
  {
    bits[i++] = (int)(original) % 2;
    original /= 2;
  }
  while (i <= 8)
  {
    bits[i++] = false;
  }
  i--;
  reverse_array(bits, i);
}

char decode_byte(const bool bits[8])
{
  int n = 0;
  for (int i = 0; i < 8; i++)
  {
    if (bits[i])
      n += pow(2, 7 - i);
  }
  return n;
}

void encode_string(const char string[], bool bytes[strlen(string) + 1][8])
{
  for (int i = 0; i <= strlen(string); i++)
  {
    encode_char(string[i], bytes[i]);
  }
}

void decode_bytes(const int rows, bool bytes[rows][8], char string[rows])
{
  for (int i = 0; i < rows; i++)
  {
    string[i] = decode_byte(bytes[i]);
  }
}

void bytes_to_blocks(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8])
{
  int set = 0, row = 0, i;
  while (set < offset)
  {
    for (i = 0; i < cols; i++)
    {
      for (int j = 0; j < 8; j++)
      {
        blocks[j + set * 8][i] = (row < rows) ? bytes[row][j] : false;
      }
      row++;
    }
    set++;
  }
}

void blocks_to_bytes(const int cols, const int offset, bool blocks[offset * 8][cols], const int rows, bool bytes[rows][8])
{
  int set = 0, col = 0;
  for (int i = 0; i < rows && set < offset; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      bytes[i][j] = blocks[set * 8 + j][col];
    }
    col++;
    if (col == cols)
    {
      col = 0;
      set++;
    }
  }
}

int main()
{
  // // 1.1
  // bool bits1[8];
  // encode_char('A', bits1);
  // for (int i = 0; i < 8; i++)
  // {
  //   printf("%d", bits1[i]);
  // }
  // printf("\n");
  // // prints: 01000001

  // // 1.2
  // bool bits2[8] = {0, 1, 0, 0, 0, 0, 0, 1};
  // printf("%c\n", decode_byte(bits2));
  // // prints: A

  // // 2.1
  // char *text = "Hello, how are you?";
  // const int len = strlen(text);
  // bool bytes1[len + 1][8];
  // encode_string(text, bytes1);
  // for (int j = 0; j <= len; j++)
  // {
  //   printf("%c: ", text[j]);
  //   for (int i = 0; i < 8; i++)
  //   {
  //     printf("%d", bytes1[j][i]);
  //   }
  //   printf("\n");
  // }

  // // 2.2
  // bool bytes2[7][8] = {
  //     {0, 1, 0, 0, 1, 0, 0, 0},
  //     {0, 1, 1, 0, 0, 1, 0, 1},
  //     {0, 1, 1, 0, 1, 1, 0, 0},
  //     {0, 1, 1, 0, 1, 1, 0, 0},
  //     {0, 1, 1, 0, 1, 1, 1, 1},
  //     {0, 0, 1, 0, 0, 0, 0, 1},
  //     {0, 0, 0, 0, 0, 0, 0, 0}};
  // char string[7];
  // decode_bytes(7, bytes2, string);
  // printf("%s\n", string);
  // // prints: Hello!

  // 3.1
  int length = 4 + 1, cols = 3, offset = 2;
  bool bytes1[4 + 1][8] = {
      {0, 1, 0, 0, 0, 0, 0, 1},
      {0, 1, 1, 0, 1, 0, 0, 0},
      {0, 1, 1, 0, 1, 1, 1, 1},
      {0, 1, 1, 0, 1, 0, 1, 0},
      {0, 0, 0, 0, 0, 0, 0, 0}};
  bool blocks1[offset * 8][cols];
  bytes_to_blocks(cols, offset, blocks1, length, bytes1);
  for (int j = 0; j < offset * 8; j++)
  {
    for (int i = 0; i < cols; i++)
    {
      printf("%d ", (blocks1[j][i] == true) ? 1 : 0);
    }
    printf("\n");
    if (j % 8 == 7)
    {
      printf("\n");
    }
  }
  // prints:
  // 0 0 0
  // 1 1 1
  // 0 1 1
  // 0 0 0
  // 0 1 1
  // 0 0 1
  // 0 0 1
  // 1 0 1
  //
  // 0 0 0
  // 1 0 0
  // 1 0 0
  // 0 0 0
  // 1 0 0
  // 0 0 0
  // 1 0 0
  // 0 0 0

  bool blocks2[2 * 8][3] = {
      {0, 0, 0},
      {1, 1, 1},
      {0, 1, 1},
      {0, 0, 0},
      {0, 1, 1},
      {0, 0, 1},
      {0, 0, 1},
      {1, 0, 1},
      {0, 0, 0},
      {1, 0, 0},
      {1, 0, 0},
      {0, 0, 0},
      {1, 0, 0},
      {0, 0, 0},
      {1, 0, 0},
      {0, 0, 0}};
  bool bytes2[length][8];
  blocks_to_bytes(3, 2, blocks2, length, bytes2);
  for (int j = 0; j < length; j++)
  {
    for (int i = 0; i < 8; i++)
    {
      printf("%d", bytes2[j][i]);
    }
    printf("\n");
  }
  // prints:
  // 01000001
  // 01101000
  // 01101111
  // 01101010
  // 00000000

  return 0;
}
