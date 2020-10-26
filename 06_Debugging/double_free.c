#include <stdio.h>
#include <stdlib.h>

int main() {
    char *a = malloc(sizeof(char));
    *a = 42;
    printf("%d\n", *a);
    free(a);
    free(a);
}
