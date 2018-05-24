#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"

// absolute values smaller than epsilon are considered zero
const double epsilon;

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
} plane;

// sphere: (x - center.x)^2 + (y - center.y)^2 + (z - center.z)^2 = radius^2
typedef struct {
	point center;
	double radius;

	// optical properties
	color col;
	material mat;
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
} collection;

// allocate and free memory for a collection of objects
collection * collection_alloc(int N_vectors, int N_rays, int N_planes,
		int N_spheres);
void collection_free(collection *bunch);

// create a gnuplot file for printing a collection of objects
// in gnuplot, type: load 'filename' 
void print_gnuplot(char *filename, collection *bunch, double x_min,
		double x_max, double y_min, double y_max, double z_min, double z_max);

/*
 * INTERSECTIONS BETWEEN TWO GEOMETRICAL OBJECTS
 */

// possible relative positions of two objects
typedef enum {
	intersecting, // regular intersection
	parallel, // for ray/ray, ray/plane, plane/plane
	skew, // for ray/ray
	contained, // one object contained in or identical to the other
	none, // for sphere/* without intersection
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
} intersection_pointlike;

// intersection data structure for plane/plane intersections
typedef struct {
	relative_position kind;
	ray g;
} intersection_linelike;

// intersection data structure for sphere/sphere and plane/sphere intersections
typedef struct {
	relative_position kind;

	// intersection occurs in a circle
	point center;
	double radius;
} intersection_circular;

// return the intersection structure with all applying details filled in

intersection_pointlike intersect_ray_ray(const ray *g, const ray *h);
intersection_pointlike intersect_ray_plane(const ray *g, const plane *E);
intersection_pointlike intersect_ray_sphere(const ray *g, const sphere *S);
intersection_linelike intersect_plane_plane(const plane *E, const plane *F);
intersection_circular intersect_plane_sphere(const plane *E, const sphere *S);
intersection_circular intersect_sphere_sphere(const sphere *S, const sphere *T);

// print the intersection details directly to screen (stdout),
// e.g.: "Rays parallel.\n"; "Intersection at (1, 0, 4).\n";

void intersection_pointlike_print(const intersection_pointlike *intersection);
void intersection_linelike_print(const intersection_linelike *intersection);
void intersection_circular_print(const intersection_circular *intersection);

/*
 * DISTANCE CALCULATIONS BETWEEN GEOMETRICAL OBJECTS
 */

// return the (minimal) distance between two objects; zero if intersecting

double distance_point_point(const point *P, const point *Q);
double distance_point_ray(const point *P, const ray *g);
double distance_point_plane(const point *P, const plane *E);
double distance_point_sphere(const point *P, const sphere *S);
double distance_ray_ray(const ray *g, const ray *h);
double distance_ray_plane(const ray *g, const plane *E);
double distance_ray_sphere(const ray *g, const sphere *S);
double distance_sphere_sphere(const sphere *S, const sphere *T);

#endif /* OBJECTS_H */

