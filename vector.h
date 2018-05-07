#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 3D vector data structure

typedef struct {
	double x, y, z;
} vec;

vec vec_create(double x, double y, double z); // returns the vector (x,y,z)
char * vec_print(vec v, int places); // represents vector as string with 'places' decimal places

// Operations

vec add(vec v, vec w); // returns the vector v + w
vec subtract(vec v, vec w); // returns the vector v - w

vec multiply(vec v, double a); // scalar multiplication - returns the vector a v
vec divide(vec v, double a); // returns the vector v/a

double dot(vec v, vec w); // inner product, returns the number v . w
vec cross(vec v, vec w); // outer product, returns the vector v x w

// Norms

double norm2(vec v); // returns the square of the Euclidean norm of v
double norm(vec v); // returns the Euclidean norm |v|
vec normalize(vec v); // returns the normalized vector v/|v|

#endif
