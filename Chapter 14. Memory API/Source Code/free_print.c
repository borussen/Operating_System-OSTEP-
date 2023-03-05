#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) 
{
    int* data = (int*) malloc(100);
    data[100] = 0;
    free(data);
    printf("%d\n", data[20]);  // print the value of one of the elements of the freed array
    return 0;
}