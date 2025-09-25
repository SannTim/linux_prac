#include <stdio.h>
#include "outlib.h"
void output(char *str) {
        printf("%d: %s\012", Count++, str);
}

void usage(char *p) {
	fprintf(stderr, "%s: v%.2f: print all\n \
			Usage: %s arg1 [...]\n", p, VERSION, p);
}
