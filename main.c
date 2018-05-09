#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// Main function: program starts here

int main() {
	vector v = vector_assign(1.0, 2.0, 0.0);
	vector w = vector_assign(-3.0, 1.0, 1.5);

	point A = vector_assign(1, 1, 1);
	point B = vector_assign(2, 0, 3);
	vector u = connect(A, B);

	printf("v = %s\n", vector_print(v, 1));
	printf("w = %s\n", vector_print(w, 1));
	printf("u = %s\n", vector_print(u, 1));
	
	return 0;
}

