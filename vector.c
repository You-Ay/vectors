#include "vector.h"

vec vec_create(double x, double y, double z) {
	vec result;
	result.x = x;
	result.y = y;
	result.z = z;
	return result;
}

void vec_print(vec v) {
	printf("( %lf , %lf , %lf )", v.x, v.y, v.z); 
}

// Implementation of further functions
