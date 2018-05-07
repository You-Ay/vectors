#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// Main function: program starts here

int main() {
	vec v = vec_create(1.0, 2.0, 0.0);
	vec w = vec_create(-3.0, 1.0, 1.5);
	
	printf("v = %s\n", vec_print(v, 1));
	printf("w = %s\n", vec_print(w, 1));
	
	return 0;
}

