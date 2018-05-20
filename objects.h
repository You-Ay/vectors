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
	material mat;
} ray;

// plane in different representations
typedef struct {
	point origin;

	// parametric form: x = origin + r direction_1 + s direction_2
	vector direction_1;
	vector direction_2;

	// normal form: (x - origin) . normal = 0
	vector normal;

	// cartesian form: a x + b y + c y = d
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
 * INTERSECTIONS BETWEEN TWO GEOMETRICAL OBJECTS
 */

// generic intersection data structure with all intersection details
typedef struct {
	// are the objects intersecting?
	// 0: no (e.g. strictly parallel planes)
	// 1: regular intersection
	// -1: one object is identical to or contained in the other
	int intersecting;

	// if intersection occurs in one point P (ray/ray, ray/plane, ray/sphere);
	point P;
	double r; // parameter of the ray at intersection point

	// if intersection occurs in one line g (plane/plane);
	ray g;

	// if intersection occurs in one circle (plane/sphere or sphere/sphere);
	point center;
	double radius;

	// intersection angle in radians (ray/ray, ray/plane, plane/plane);
	double angle;
} intersection;

// return the intersection structure with all applying details filled in

intersection intersect_ray_ray(const ray *g, const ray *h);
intersection intersect_ray_plane(const ray *g, const plane *E);
intersection intersect_ray_sphere(const ray *g, const sphere *S);
intersection intersect_plane_plane(const plane *E, const plane *F);
intersection intersect_plane_sphere(const plane *E, const sphere *S);
intersection intersect_sphere_sphere(const sphere *S, const sphere *T);

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

