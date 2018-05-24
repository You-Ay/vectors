#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "objects.h"

// Main function: program starts here

int main() {
	/*
	 * VECTOR OPERATIONS
	 */

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

	/*
	 * GNUPLOT TESTING
	 */
	
	// some ray
	
	vector u_g = vector_assign(1, 0, 0);
	vector v_g = vector_assign(1, 1, 0);
	ray g = ray_assign(u_g, v_g);
	
	// some plane 
	
	vector a_E = vector_assign(0, 0, -1);
	vector u_E = vector_assign(1, 0, 0);
	vector v_E = vector_assign(0, 1, 0);
	plane E = plane_assign_parametric(a_E, u_E, v_E);

	// some spheres
	
	vector c_1 = vector_assign(0, 0, 0);
	double r_1 = 2;
	sphere S_1 = sphere_assign(c_1, r_1);

	vector c_2 = vector_assign(0, 0, 3);
	double r_2 = 1;
	sphere S_2 = sphere_assign(c_2, r_2);

	
	// put everything into a collection structure
	
	// allocate for 2 vectors, 1 ray, 1 plane, 2 spheres
	collection *bunch = collection_alloc(2, 1, 1, 2);

	bunch->vectors[0] = v;
	bunch->vectors[1] = w;

	bunch->rays[0] = g;

	bunch->planes[0] = E;

	bunch->spheres[0] = S_1;
	bunch->spheres[1] = S_2;

	print_gnuplot("plot.txt", bunch, -6, 6, -6, 6, -2, 4);

	// free allocated memory
	collection_free(bunch);
	
	return 0;
}

