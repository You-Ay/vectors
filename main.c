#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "objects.h"

// Main function: program starts here

int main() {
	// Some testing of recently added routines

	vector v = vector_assign(1.0, 2.0, 0.0);
	vector w = vector_assign(-3.0, 1.0, 1.5);

	printf("    v = %s\n", vector_print(v, 1));
	printf("    w = %s\n", vector_print(w, 1));

	printf("v + w = %s\n", vector_print(add(v, w), 1));
	printf("v - w = %s\n", vector_print(subtract(v, w), 1));
	printf("  2 v = %s\n", vector_print(multiply(v, 2), 1));
	printf("w / 2 = %s\n", vector_print(divide(w, 2), 2));
	printf("v . w = %f\n", dot(v, w));
	printf("v x w = %s\n", vector_print(cross(v, w), 1));
	printf("||v|| = %f\n", norm(v));
	printf("v_nor = %s\n", vector_print(normalize(v), 3));
	
	return 0;
}

