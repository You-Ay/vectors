#include "vector.h"

vec vec_create(double x, double y, double z) {
	vec result;
	result.x = x;
	result.y = y;
	result.z = z;
	return result;
}

char * vec_print(vec v, int places) {
	static char result[100];
	sprintf(result, "( %0.*f , %0.*f , %0.*f )", places, v.x,
			places, v.y, places, v.z); 
	return result;
}

// Implementation of further functions

