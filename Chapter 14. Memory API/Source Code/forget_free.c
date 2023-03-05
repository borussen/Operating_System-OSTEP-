#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) 
{
    int* ptr = (int*) malloc(sizeof(int));
    *ptr = 1;
    printf("%d\n", *ptr);
    return 0;
}