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
	
	vector a_E = vector_assign(2, 2, 0);
	vector u_E = vector_assign(1, 1, -1);
	vector v_E = vector_assign(5, -1, -1);
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
	printf("E : %s\n", plane_print_parametric(E, 0));
	printf("E : %s\n", plane_print_normal(E, 0));
	printf("E : %s\n", plane_print_cartesian(E, 0));
	printf("S : %s\n", sphere_print(S_1, 0));
	
	/*
	 * CHECKING VECTORS FOR EQUALITY, PARALLELITY, ORTHOGONALITY
	 */

	vector a = vector_assign(1, 0, 0);
	vector b = vector_assign(0, 1, 0);
	vector c = vector_assign(0, -2, 0);
	vector d = vector_assign(0.0, -2.0, 0.0);

	printf("a = %s ", vector_print(a, 0));
	printf("and b = %s ", vector_print(b, 0));

	if (are_orthogonal(a, b))
		printf("are orthogonal.\n");
	else
		printf("are not orthogonal.\n");
	
	printf("b = %s ", vector_print(b, 0));
	printf("and c = %s ", vector_print(c, 0));

	if (are_collinear(b, c))
		printf("are collinear.\n");
	else
		printf("are not collinear.\n");
	
	printf("c = %s ", vector_print(c, 0));
	printf("and d = %s ", vector_print(d, 0));

	if (are_equal(c, d))
		printf("are equal.\n");
	else
		printf("are not equal.\n");

	/*
	 * INTERSECTION TESTING
	 */

	vector u_h = vector_assign(0, 0, 0);
	vector v_h = vector_assign(1, 0, 0);
	ray h = ray_assign(u_h, v_h);

	intersection I_gh = intersect_ray_ray(&g, &h);
	intersection I_gE = intersect_ray_plane(&g, &E);
	intersection I_gS = intersect_ray_sphere(&g, &S_1);
	
	intersection_print_ray_ray(&I_gh, 1);
	intersection_print_ray_plane(&I_gE, 1);
	intersection_print_ray_sphere(&I_gS, 1);

	return 0;
}

