#include "outlib.h"
int main(int argc, char *argv[]) {
    Count = argc;
	if ((Count = argc) > 1)
		for (int i = 1; i < argc; i++)
			output(argv[i]);
	else{
		// usage(argv[0]);
		usage("prog");
	}
    return 0;
}
