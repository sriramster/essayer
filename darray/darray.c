#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int * items;
    size_t count;
    size_t capacity;
} IArray;

typedef struct {
    float * items;
    size_t count;
    size_t capacity;
} FArray;

typedef struct {
    const char * items;
    size_t count;
    size_t capacity;
} SArray;

#define d_append(xs, x)                                                 \
    do {                                                                \
        if (xs.count >= xs.capacity) {                                  \
            if (xs.count  == 0) xs.capacity = 256;                      \
            else xs.capacity *= 2;                                      \
            xs.items = realloc(xs.items, xs.capacity * sizeof(*xs.items)); \
        }                                                               \
        xs.items[xs.count++] = x;                                       \
    } while (0);                                                        \

int main() {
    IArray d = {0};

    for (int i = 0; i < 10 ; i++) d_append(d, i);
    for (size_t s = 0; s < d.count; s++)
        printf("%d\n", d.items[s]);

    FArray f = {0};
    for (int i = 0; i < 10 ; i++) d_append(f, i);
    for (size_t s = 0; s < d.count; s++)
        printf("%f\n", f.items[s]);

    return 0;
}
