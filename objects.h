#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"

/*
 * DATA TYPES FOR GEOMETRICAL OBJECTS
 */

// ray: x = origin + r direction
typedef struct {
	point origin;
	vector direction;

	// optical properties
	color col;
} ray;

// plane in different representations
typedef struct {
	point origin;

	// parametric form: x = origin + r direction_1 + s direction_2
	vector direction_1;
	vector direction_2;

	// normal form: (x - origin) . normal = 0
	vector normal;

	// cartesian form: a x + b y + c z = d
	double a, b, c, d;

	// optical properties
	color col;
	material mat;
	bool is_light_source;
} plane;

// parametric form: x = origin + r direction_1 + s direction_2 with r+s<=1, r>=0 and s>=0
// the triangle needs to be assigned parametric or by points!
typedef plane triangle;

// sphere: (x - center.x)^2 + (y - center.y)^2 + (z - center.z)^2 = radius^2
typedef struct {
	point center;
	double radius;

	// optical properties
	color col;
	material mat;
	bool is_light_source;
} sphere;

/*
 * ASSIGNING AND PRINTING GEOMETRICAL OBJECTS (WITHOUT OPTICAL PROPERTIES)
 */

ray ray_assign(point origin, vector direction);
ray ray_assign_points(point A, point B); // A and B are on the ray

// represents ray as string, e.g. "x = (1, 0, 0) + r (2, -1, 1)",
// numbers with 'places' decimal places
char * ray_print(ray g, int places);

// return plane in all representations, starting from one
plane plane_assign_parametric(point origin, vector direction_1,
		vector direction_2);
plane plane_assign_normal(point origin, vector normal);
plane plane_assign_cartesian(double a, double b, double c, double d);
plane plane_assign_points(point A, point B, point C); // A, B, C on the plane

// fonctions to represent plane as string in different forms:
// parametric, e.g.: "x = (1, 0, 0) + r (2, -1, 1) + s (0, 0, 1)"
// normal, e.g.: "[x - (1, 0, 0)] . (-1, -2, 0) = 0"
// cartesian, e.g.: "-1 x - 2 y + 0 z = -1"
// numbers with 'places' decimal places
char * plane_print_parametric(plane E, int places);
char * plane_print_normal(plane E, int places);
char * plane_print_cartesian(plane E, int places);

sphere sphere_assign(point center, double radius);

// represents sphere as string, e.g. "(x - 2)^2 + (y + 1)^2 + (z - 0)^2 = 5^2",
// numbers with 'places' decimal places
char * sphere_print(sphere S, int places);

/*
 * PLOTTING A COLLECTION OF OBJECTS BY GNUPLOT
 */

// data structure for storing a collection of objects
typedef struct {
	vector *vectors;
	int N_vectors;

	ray *rays;
	int N_rays;

	plane *planes;
	int N_planes;

	sphere *spheres;
	int N_spheres;

	triangle *triangles;
	int N_triangles;
} collection;

// allocate and free memory for a collection of objects
collection * collection_alloc(int N_vectors, int N_rays, int N_planes,
		int N_spheres, int N_triangles);
void collection_free(collection *bunch);

// allocate and fill a collection of objects:
// The speficiation may read "vvrpss" for creating to vectors, one ray,
// one plane and two spheres; the same number of corresponding objects
// has then to be passed.
collection * collection_assign(char *specification, ...);

// create a gnuplot file for printing a collection of objects
// in gnuplot, type: load 'filename' 
void print_gnuplot(char *filename, collection *bunch, double x_min,
		double x_max, double y_min, double y_max, double z_min, double z_max);

// create a TXT file with a geogebra command to be copied & pasted into
// the geogebra 3D input line
void print_geogebra(char *filename, collection *bunch);

/*
 * INTERSECTIONS BETWEEN TWO GEOMETRICAL OBJECTS
 */

// possible relative positions of two objects
typedef enum {
	intersecting, // regular intersection
	parallel, // for ray/ray, ray/plane
	skew, // for ray/ray
	contained, // one object contained in or identical to the other
	none, // for ray/sphere without intersection
} relative_position;

// intersection data structure for ray/* intersections
typedef struct {
	relative_position kind;

	// point and value of the ray's parameter r at the intersection
	point P;
	double r;

	// in case of ray/sphere, there is a 2nd intersection,
	// (potentially identical to the 1st if ray is tangential)
	point P_2;
	double r_2;
} intersection;

// return the intersection structure with all applying details filled in

intersection intersect_ray_ray(const ray *g, const ray *h);
intersection intersect_ray_plane(const ray *g, const plane *E);
intersection intersect_ray_sphere(const ray *g, const sphere *S);
intersection intersect_ray_triangle(const ray *g, const triangle *T);

// print the intersection details directly to screen (stdout),
// e.g.: "Rays parallel.\n"; "Intersection at (1, 0, 4).\n";

void intersection_print_ray_ray(const intersection *I, int places);
void intersection_print_ray_plane(const intersection *I, int places);
void intersection_print_ray_sphere(const intersection *I, int places);
void intersection_print_ray_triangle(const intersection *I, int places);

#endif /* OBJECTS_H */

