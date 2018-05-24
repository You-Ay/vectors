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

	return result;
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

	return result;
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

	return result;
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

collection * collection_alloc(int N_vectors, int N_rays, int N_planes,
		int N_spheres) {

	collection *bunch = malloc(sizeof(collection));

	bunch->vectors = malloc(N_vectors * sizeof(vector));
	bunch->N_vectors = N_vectors;

	bunch->rays = malloc(N_rays * sizeof(ray));
	bunch->N_rays = N_rays;

	bunch->planes = malloc(N_planes * sizeof(plane));
	bunch->N_planes = N_planes;

	bunch->spheres = malloc(N_spheres * sizeof(sphere));
	bunch->N_spheres = N_spheres;

	return bunch;
}

void collection_free(collection *bunch) {
	free(bunch->vectors);
	free(bunch->rays);
	free(bunch->planes);
	free(bunch->spheres);
	free(bunch);
}

void print_gnuplot(char *filename, collection *bunch, double x_min,
		double x_max, double y_min, double y_max, double z_min, double z_max) {

	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		fprintf(stderr, "Error opening file %s.\n", filename);
		return;
	}

	// gnuplot settings 
	
	fprintf(file, "set nokey\n");
	fprintf(file, "set parametric\n");
	fprintf(file, "set hidden3d\n");
	fprintf(file, "set samples 25\n");
	fprintf(file, "set isosamples 30, 20\n");
	fprintf(file, "set xrange [%f:%f]\n", x_min, x_max);
	fprintf(file, "set yrange [%f:%f]\n", y_min, y_max);
	fprintf(file, "set zrange [%f:%f]\n", z_min, z_max);
	fprintf(file, "set multiplot\n");

	int color_counter = 1;

	// plot position vectors
	
	for (int i = 0; i < bunch->N_vectors; i++) {
		fprintf(file, "set arrow %d from 0, 0, 0 to %f, %f, %f\n",
				i+1, bunch->vectors[i].x, bunch->vectors[i].y,
				bunch->vectors[i].z);
	}

	// plot rays
	
	for (int i = 0; i < bunch->N_rays; i++) {
		fprintf(file, "splot %f+%f*u, ",
				bunch->rays[i].origin.x, bunch->rays[i].direction.x);
		fprintf(file, "%f+%f*u, ",
				bunch->rays[i].origin.y, bunch->rays[i].direction.y);
		fprintf(file, "%f+%f*u ",
				bunch->rays[i].origin.z, bunch->rays[i].direction.z);
		fprintf(file, "lc %d\n", color_counter++);
	}

	// plot planes
	
	for (int i = 0; i < bunch->N_planes; i++) {
		fprintf(file, "splot %f+%f*u+%f*v, ",
				bunch->planes[i].origin.x, bunch->planes[i].direction_1.x,
				bunch->planes[i].direction_2.x);
		fprintf(file, "%f+%f*u+%f*v, ",
				bunch->planes[i].origin.y, bunch->planes[i].direction_1.y,
				bunch->planes[i].direction_2.y);
		fprintf(file, "%f+%f*u+%f*v ",
				bunch->planes[i].origin.z, bunch->planes[i].direction_1.z,
				bunch->planes[i].direction_2.z);
		fprintf(file, "lc %d\n", color_counter++);
	}

	// plot spheres

	for (int i = 0; i < bunch->N_spheres; i++) {
		fprintf(file, "splot [-pi:pi][-pi/2:pi/2] %f*(cos(u)*cos(v)+%f), ",
				bunch->spheres[i].radius, bunch->spheres[i].center.x);
		fprintf(file, "%f*(sin(u)*cos(v)+%f), ",
				bunch->spheres[i].radius, bunch->spheres[i].center.y);
		fprintf(file, "%f*(sin(v)+%f) ",
				bunch->spheres[i].radius, bunch->spheres[i].center.z);
		fprintf(file, "lc %d\n", color_counter++);
	}

	fprintf(file, "unset multiplot\n");

	fclose(file);
}

// Implementation of the functions declared in the header objects.h

