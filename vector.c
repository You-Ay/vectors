#include "vector.h"

vector vector_assign(double x, double y, double z) {
	vector result;
	result.x = x;
	result.y = y;
	result.z = z;
	return result;
}

vector connect(point A, point B) {
	vector result;
	result.x = B.x - A.x;
	result.y = B.y - A.y;
	result.z = B.z - A.z;
	return result;
}

char * vector_print(vector v, int places) {
	static char result[255];
	sprintf(result, "( %0.*f , %0.*f , %0.*f )", places, v.x,
			places, v.y, places, v.z); 
	return result;
}

// Implementation of further functions

