#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// 3D vector data structure
typedef struct {
	double x, y, z;
} vector;

/*
 * ALTERNATIVE USES OF THE VECTOR STRUCTURE
 */

// point as position vector
typedef vector point;

// color as vector RGB (x: red, y: green, z: blue), each from 0 to 1
typedef vector color;

// material as a percentage of "paper" (x), "mirror" (y), "glass" (z)
typedef vector material;

/*
 * ASSIGNING AND PRINTING VECTORS
 */

// returns the vector (x,y,z)
vector vector_assign(double x, double y, double z);

// returns the vector from point A to point B
vector connect(point A, point B);

// represents vector as string with 'places' decimal places
char * vector_print(vector v, int places);

/*
 * OPERATIONS ON VECTORS
 */

// returns the vector v + w
vector add(vector v, vector w);

// returns the vector v - w
vector subtract(vector v, vector w);

// multiplication with scalar - returns the vector a v
vector multiply(vector v, double a);

// division by scalar - returns the vector v/a
vector divide(vector v, double a);

// inner product, returns the number v . w
double dot(vector v, vector w);

// outer product, returns the vector v x w
vector cross(vector v, vector w);

/*
 * NORMS AND NORMALIZATION
 */

// returns the square of the Euclidean norm of v
double norm2(vector v);

// returns the Euclidean norm |v|
double norm(vector v);

// returns the normalized vector v/|v|
vector normalize(vector v);

/*
 * CHECKS FOR EQUALITY, PARALLELITY, ORTHOGONALITY
 */

// avoid floating point precision errors:
// absolute values smaller than epsilon are considered zero
extern const double epsilon;

// return true if vectors satisfy condition up to a difference of epsilon,
// false otherwise

bool are_equal(vector v, vector w); 
bool are_collinear(vector v, vector w);
bool are_orthogonal(vector v, vector w);

#endif /* VECTOR_H */

