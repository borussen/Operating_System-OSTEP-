#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) 
{
    int* ptr = NULL;
    printf("%d\n", *ptr);  // deference the NULL pointer
    return 0;
}