#include "objects.h"

ray ray_assign(point origin, vector direction) {

	ray result;

	result.origin = origin;

	result.direction = vector_assign(direction.x, direction.y, direction.z);

	return result;

}

ray ray_assign_points(point A, point B) {

	ray result;

	result.origin = A;

	result.direction = subtract(B, A);

	return result;

}

plane plane_assign_parametric(point origin, vector direction_1, vector direction_2) {

	plane result;

	result.origin = origin;

	result.direction_1 = direction_1;
	result.direction_2 = direction_2;

	result.normal = cross(direction_1, direction_2);

	result.a = result.normal.x;
	result.b = result.normal.y;
	result.c = result.normal.z;
	result.d = dot(result.normal, origin);

}

plane plane_assign_normal(point origin, vector normal) {

	plane result;

	result.origin = origin;

	result.normal = normal;

	// (Probably) turns the normal vector by 90 degrees, (probably) works somehow
	if(normal.x != 0 || normal.y != 0) {

		result.direction_1 = vector_assign(normal.y * -1, normal.x, 0);

	} else if(normal.z != 0) {

		result.direction_1 = vector_assign(0, normal.z * -1, normal.y);

	} else {

		fprintf(stderr, "Error - unable to assign plane with normal zero vector!");

	}

	result.direction_2 = cross(normal, result.direction_1);

	result.a = normal.x;
	result.b = normal.y;
	result.c = normal.z;
	result.d = dot(normal, origin);

}

plane plane_assign_cartesian(double a, double b, double c, double d) {

	plane result;

	result.a = a;
	result.b = b;
	result.c = c;
	result.d = d;

	result.normal = vector_assign(a, b, c);

	// (Probably) turns the normal vector by 90 degrees, (probably) works somehow
	if(result.normal.x != 0 || result.normal.y != 0) {

		result.direction_1 = vector_assign(result.normal.y * -1, result.normal.x, 0);

	} else if(result.normal.z != 0) {

		result.direction_1 = vector_assign(0, result.normal.z * -1, result.normal.y);

	} else {

		fprintf(stderr, "Error - unable to assign plane with all parameter zero !");

	}

	result.direction_2 = cross(result.normal, result.direction_1);

}

plane plane_assign_points(point A, point B, point C) {

	plane result;

	result.origin = A;

	result.direction_1 = subtract(B, A);
	result.direction_2 = subtract(C, A);

	result.normal = cross(result.direction_1, result.direction_2);

	result.a = result.normal.x;
	result.b = result.normal.y;
	result.c = result.normal.z;
	result.d = dot(result.normal, result.origin);

	return result;

}

sphere sphere_assign(point center, double radius) {

	sphere result;

	result.center = center;

	result.radius = radius;

	return result;

}

// Implementation of the functions declared in the header objects.h
