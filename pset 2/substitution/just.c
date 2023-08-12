#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *first_malloc_pointer = malloc(2 * sizeof(int));
    first_malloc_pointer[0] = 1;
    first_malloc_pointer[1] = 2;

    int *realloc_pointer = realloc( first_malloc_pointer, 11 * sizeof(int));

    first_malloc_pointer = realloc_pointer;

    first_malloc_pointer[2] = 4;
    first_malloc_pointer[3] = 3;
    first_malloc_pointer[4] = 6;
    first_malloc_pointer[5] = 2;

    for (int i = 0; i <= 11; i++)
    {
        printf("%d\n",first_malloc_pointer[i]);
    }
    free(first_malloc_pointer);
}
