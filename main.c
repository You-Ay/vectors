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
	 * GNUPLOT AND GEOGEBRA TESTING
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

	collection *bunch = collection_assign("vvrpss", v, w, g, E, S_1, S_2);

	// call gnuplot and geogebra print

	print_gnuplot("gnuplot.txt", bunch, -6, 6, -6, 6, -2, 4);
	print_geogebra("geogebra.txt", bunch);

	// free allocated memory
	
	collection_free(bunch);

	/*
	 * PRINTING OBJECTS TO STDOUT TESTING
	 */

	printf("g : %s\n", ray_print(g, 0));

	/*
	 * CHECKING VECTORS FOR EQUALITY, PARALLELITY, ORTHOGONALITY
	 */

	vector a = vector_assign(1, 0, 0);
	vector b = vector_assign(0, 1, 0);
	vector c = vector_assign(0, -2, 0);

	printf("a = %s and b = %s are ", vector_print(a, 0), vector_print(b, 0));

	if (are_orthogonal(a, b))
		printf("orthogonal.\n");
	else
		printf("not orthogonal.\n");
	
	printf("b = %s and c = %s are ", vector_print(b, 0), vector_print(c, 0));

	if (are_orthogonal(b, c))
		printf("orthogonal.\n");
	else
		printf("not orthogonal.\n");
	
	return 0;
}

