#include "globals.h"

//from https://forums.quectel.com/t/linker-error-undefined-reference-to-sbrk/3509/3
void *_sbrk(int incr) {
	return (void *)-1;
}
