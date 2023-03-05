#include <stdio.h>
#include <stdlib.h>

typedef struct vector {
    int* data;
    int capacity;
    int size;
} Vector;

void insert(Vector* v, int value);
void delete(Vector* v);
int get(Vector* v, int index);
void freeVector(Vector* v);

int main (int argc, char* argv[]) 
{
    Vector v = {.data = (int*) malloc(sizeof(int)), .capacity = 1, .size = 1};
    v.data[0] = 10;

    Vector* vp = &v;

    insert(vp, 20);
    delete(vp);
    insert(vp, 30);
    insert(vp, 40);

    printf("%d %d %d\n", get(vp, 0), get(vp, 1), get(vp, 2));
    printf("vector capacity: %d\n", v.capacity);
    printf("vector size: %d\n", v.size);

    freeVector(vp);
    return 0;
}

void insert(Vector* v, int value) {
    if (v->size >= v->capacity) {
        v->data = (int*) realloc (v->data, (v->capacity + 1) * sizeof(int));
        v->capacity++;
    }
    (v->data)[v->size++] = value;
}

void delete(Vector* v) {
    if (v->size > 0) {
        v->data[--(v->size)] = 0;
    }
}

int get(Vector* v, int index) {
    return v->data[index];
}

void freeVector(Vector* v) {
    free(v->data);
    v->size = 0;
    v->capacity = 0;
}