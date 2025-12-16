#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int start = 0;
    int end = 0;
    int step = 1;
    int current = 0;
    
    if (argc < 2 || argc > 4) {
        printf("Usage: %s [start] end [step]\n", argv[0]);
        printf("  With 1 argument: range(0, end, 1)\n");
        printf("  With 2 arguments: range(start, end, 1)\n");
        printf("  With 3 arguments: range(start, end, step)\n");
        return 1;
    }
    
    if (argc == 2) {
        // range(N)
        end = atoi(argv[1]);
        start = 0;
        step = 1;
    } else if (argc == 3) {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
        step = 1;
    } else if (argc == 4) {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
        step = atoi(argv[3]);
    }
    
    if (step == 0) {
        fprintf(stderr, "Error: step cannot be zero\n");
        return 1;
    }
    
    if (step > 0) {
        for (current = start; current < end; current += step) {
            printf("%d\n", current);
        }
    } else {
        for (current = start; current > end; current += step) {
            printf("%d\n", current);
        }
    }

    return 0;
}
