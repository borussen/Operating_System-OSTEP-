#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define PAGESIZE 4096

int main (int argc, char* argv[])
{
    if (argc != 3) {
        fprintf(stderr, "USAGE: tlb <number of pages> <number of trials>\n");
        return 1;
    }

    int numPages = atoi(argv[1]);
    int numTrials = atoi(argv[2]);

    if (numPage2 <= 0 || numTrials <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    struct timeval start, end;
    int jump = PAGESIZE / sizeof(int);
    int* a = malloc(numPage * jump * sizeof(int));

    for (int i = 0; i < numPages * jump; i++) {
        a[i] = 1;
    }

    gettimeofday(&start, NULL);

    for (int i = 0; i < numTrials; i++) {
        for (int j = 0; j < numPages * jump; j+= jump) {
            a[j] += 1;
        }
    }

    gettimeofday(&end, NULL);

    // nanoseconds
    long time = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_usec - start.tv_usec) * 1000;
    double average = time / (numPages * numTrials);
    printf("%f\n", average);

    free(a);

    return 0;
}