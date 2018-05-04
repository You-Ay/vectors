#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// Main function: program starts here

int main() {
	vec v = vec_create(1.0, 2.0, 0.0);
	vec w = vec_create(-3.0, 1.0, 1.5);
	
	printf("v = ");
	vec_print(v);
	printf("\n");
	
	printf("w = ");
	vec_print(w);
	printf("\n");
	
	return 0;
}
