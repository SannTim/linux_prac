#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        fprintf(stderr, "Usage:\n"
                        "  %s N                -> 0 .. N-1\n"
                        "  %s M N              -> M .. N-1\n"
                        "  %s M N S            -> M, M+S, M+2S, ... < N\n",
                argv[0], argv[0], argv[0]);
        return 1;
    }

    long start, stop, step = 1;
    long current, number=0;

    if (argc == 2) {
        start = 0;
        stop = atol(argv[1]);
    } else if (argc == 3) {
        start = atol(argv[1]);
        stop = atol(argv[2]);
    } else { // argc == 4
        start = atol(argv[1]);
        stop = atol(argv[2]);
        step = atol(argv[3]);
        if (step == 0) {
            fprintf(stderr, "Error: step must not be zero\n");
            return 1;
        }
    }

    current = start;

    // Проверка направления шага
    if ((step > 0 && start >= stop) || (step < 0 && start <= stop)) {
        return 0;
    }

    while ((step > 0 && current < stop) || (step < 0 && current > stop)) {
        printf("%ld\n", number);
        current += step;
		number+=current;
	}

    return 0;
}
