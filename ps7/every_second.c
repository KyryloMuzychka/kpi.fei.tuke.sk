#include <stdio.h>
#include <stdbool.h>

#define MAX 500

int DeleteStop(char result[], int size_result, char stop[], int size_stop)
{
    int j = 0, i;
    for (i = 0; i < size_result; i++)
    {
        if (result[i] == stop[j] && j < size_stop)
        {
            j++;
        }
        else if (j == size_stop)
        {
            result[i - size_stop] = '\0';
            break;
        }
        else
        {
            j = 0;
        }
    }
    return i - size_stop;
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (file == NULL || output == NULL)
    {
        perror("Error opening files");
        return 1;
    }

    char start[] = "START", result[MAX];
    char stop[] = "STOP", output_array[MAX];
    int sizeStart = sizeof(start) / sizeof(start[0]) - 1, index = 0, i = 0;
    bool write = false;
    
    do {
    int c = fgetc(file);

    if (c != EOF) {
        if (c == start[index] && index < sizeStart) {
            index++;
        } else {
            index = 0;
        }
    } else {
        break;
    }

    } while (!(index == sizeStart));

    
    fgetc(file);
    
    if (index == sizeStart)
    {
        char c;

        while (!feof(file))
        {
            c = fgetc(file);
            result[i++] = c;                        
        }
        
        // printf("%s\n", result);

        result[i]= '\0';

        i = DeleteStop(result, i, stop, 4);
        
        // printf("i = %i", i);

        int y = 0;

        for (int j = 0; j < i; j++)    
        {
          if (result[j] == ' ')
          {      
            if (!write && y != 0)
            {              
              output_array[y++] = result[j];
            }        
            write = !write;
          }
            else if (write)
            {
               output_array[y++] = result[j];
            }
        }

        output_array[y] = '\0';

        // printf("%s\n", result);

        // printf("%s\n", output_array);

        for (int k = 0; k < y; k++)
        {
            fputc(output_array[k], output);
        }
        
    }

    fclose(file);
    fclose(output);

    return 0;
}
