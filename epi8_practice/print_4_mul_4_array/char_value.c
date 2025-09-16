#include <stdio.h>
#include <stdlib.h>

// #define the dimensions for clarity

#define DIM1 3
#define DIM2 6
#define DIM3 4
#define DIM4 5

int main(void) {
  static const unsigned char char_value[3][6][4][5] = {
      {0},
      {{0},
       {
           {0},
           {
               {0},
               ' ',
           },
       },
       {
           {0},
           {0},
           {
               {0},
               {0},
               {0},
               'A',
           },
           {
               {0},
               {0},
               {0},
               {0},
               'x',
           },

       },
       {{0},
        {0},
        {
            {0},
            {0},
            0xf3,
        }},
       {
           {0},
           {0},
           {
               {0},
               {0},
               {0},
               '\n',
           },
       }

      },
      {
          {0},
          {
              {0},
              {{0}, {0}, 0320},
          },
          {{0}, {{0}, '0'}, {{0}, {0}, '\''}, {{0}, '\121'}},
          {0},
          {
              {0},
              {0},
              {0},
              {
                  {0},
                  {0},
                  '3',
                  3,
              },
          },
          {
              {0},
              {0},
              {0},
              {
                  {0},
                  {0},
                  {0},
                  {0},
                  125,
              },
          },
      },

  };

  printf("依次打印各个位置对应的字符：\n");
  // Iterate through the array using four nested loops

  for (int i = 0; i < DIM1; i++) {
    for (int j = 0; j < DIM2; j++) {
      for (int k = 0; k < DIM3; k++) {
        for (int l = 0; l < DIM4; l++) {
          // check if the current element is non-zero
          if (char_value[i][j][k][l] != 0) {
            // print the value and its indices
            printf("Value: '%c' (0x%x), Indices: [%d][%d][%d][%d]\n",
                   char_value[i][j][k][l], char_value[i][j][k][l], i, j, k, l);
          }
        }
      }
    }
  }
  // 这是最有效率的循环遍历是因为按照行主序的顺序进行遍历(directly follows the
  // row-major storage order)

  /*
   *Cache Locality: By iterating through the array in this way, you access
   memory addresses that are close to each other. When your program reads a
   value, the CPU's cache line loads a block of nearby memory. The next value
   you need is likely already in this fast cache, resulting in a high cache hit
   rate and significantly faster performance.

   Simplicity and Readability: This
   code is easy to read and understand. The logic directly maps to the array's
   structure, making it less prone to errors than complex pointer arithmetic or
   manual address calculations.
   *
   * */

  return EXIT_SUCCESS;
}
