#include "vector.h"

const double epsilon = 1e-6;

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
	sprintf(result, "(%0.*f, %0.*f, %0.*f)", places, v.x,
			places, v.y, places, v.z); 
	return result;
}

vector add(vector v, vector w) {

	vector result;

	result.x = v.x + w.x;
	result.y = v.y + w.y;
	result.z = v.z + w.z;

	return result;

}

vector subtract(vector v, vector w) {

	vector result;

	result.x = v.x - w.x;
	result.y = v.y - w.y;
	result.z = v.z - w.z;

	return result;

}

vector multiply(vector v, double a) {

	vector result;

	result.x = v.x * a;
	result.y = v.y * a;
	result.z = v.z * a;

	return result;

}

vector divide(vector v, double a) {

	vector result;

	result.x = v.x / a;
	result.y = v.y / a;
	result.z = v.z / a;

	return result;

}

double dot(vector v, vector w) {

	double result = v.x * w.x + v.y * w.y + v.z * w.z;

	return result;

}

vector cross(vector v, vector w) {

	vector result;

	result.x = v.y * w.z - v.z * w.y;
	result.y = v.z * w.x - v.x * w.z;
	result.z = v.x * w.y - v.y * w.x;

	return result;

}

double norm2(vector v) {

	return v.x * v.x + v.y * v.y + v.z * v.z;

}

double norm(vector v) {

	return sqrt(norm2(v));

}

vector normalize(vector v) {

	double length = norm(v);

	if(length != 0) {

		vector result;

		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;

		return result;

	} else {

		fprintf(stderr, "Error - unable to normalize zero vector! Returned zero vector instead.");
		return v;

	}

}

// for the checking functions, we assume that the vector norms are not
// huge, because this could trick the comparison with epsilon
// (alternative: normalize vectors before checks, but doing this every
// time is numerically expensive.

bool are_equal(vector v, vector w) {
	return (norm2(subtract(v, w)) < epsilon*epsilon);
}

bool are_collinear(vector v, vector w) {
	return (norm2(cross(v, w)) < epsilon*epsilon);
}

bool are_orthogonal(vector v, vector w) {
	return (fabs(dot(v, w)) < epsilon);
}

