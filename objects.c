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

char *ray_print(ray g, int places) {
    static char result[255];
    sprintf(result, "x = (%0.*f, %0.*f, %0.*f) + r (%0.*f, %0.*f, %0.*f)",
    places, g.origin.x, places, g.origin.y, places, g.origin.z,
    places, g.direction.x, places, g.direction.y, places, g.direction.z);

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

	result.is_light_source = false;

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

	result.is_light_source = false;

	return result;
}

plane plane_assign_cartesian(double a, double b, double c, double d) {

	plane result;

	result.a = a;
	result.b = b;
	result.c = c;
	result.d = d;

	result.normal = vector_assign(a, b, c);

	if (result.a != 0)
		result.origin = vector_assign(d/a, 0, 0);
	else if (result.b != 0)
		result.origin = vector_assign(0, d/b, 0);
	else if (result.c != 0)
		result.origin = vector_assign(0, 0, d/c);
	else
		fprintf(stderr, "Error - unable to assign plane with normal zero vector!");

	// (Probably) turns the normal vector by 90 degrees, (probably) works somehow
	if(result.normal.x != 0 || result.normal.y != 0) {

		result.direction_1 = vector_assign(result.normal.y * -1, result.normal.x, 0);

	} else if(result.normal.z != 0) {

		result.direction_1 = vector_assign(0, result.normal.z * -1, result.normal.y);

	} else {

		fprintf(stderr, "Error - unable to assign plane with all parameter zero !");

	}

	result.direction_2 = cross(result.normal, result.direction_1);

	result.is_light_source = false;

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

	result.is_light_source = false;

	return result;

}

char *plane_print_parametric (plane E, int places) {
    static char result[255];
    sprintf(result, "x = (%0.*f, %0.*f, %0.*f) + r (%0.*f, %0.*f, %0.*f) + s (%0.*f, %0.*f, %0.*f)",
    places, E.origin.x, places, E.origin.y, places, E.origin.z,
    places, E.direction_1.x, places, E.direction_1.y, places, E.direction_1.z,
    places, E.direction_2.x, places, E.direction_2.y, places, E.direction_2.z);
   
    return result;
}


char *plane_print_normal (plane E, int places) {
    static char result[255];
    sprintf(result, "[x - (%0.*f, %0.*f, %0.*f)] . (%0.*f, %0.*f, %0.*f) = 0",
    places, E.origin.x, places, E.origin.y, places, E.origin.z,
    places, E.normal.x, places, E.normal.y, places, E.normal.z);
   
    return result;
}

char *plane_print_cartesian (plane E, int places) {
    static char result[255];
    sprintf(result, "%0.*f x %+0.*f y %+0.*f z = %0.*f ",
    places, E.a, places, E.b, places, E.c, places, E.d);

    return result;
}

sphere sphere_assign(point center, double radius) {

	sphere result;

	result.center = center;

	result.radius = radius;

	result.is_light_source = false;

	return result;

}

char *sphere_print(sphere S, int places) {
    static char result[255];
    sprintf(result, "(x %+0.*f)^2 + (y %+0.*f)^2 + (z %+0.*f)^2= (%0.*f) ^2",
    places, -1 * S.center.x, places, -1 * S.center.y, places, -1 * S.center.z,
    places, S.radius);

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

collection * collection_assign(char * specification, ...) {

	// go through specification character by character and remember numbers
	
	const char *p;

	int N_vectors = 0;
	int N_rays = 0;
	int N_planes = 0;
	int N_spheres = 0; 

	for (p = specification; *p != '\0'; p++) {
		switch (*p) {
		case 'v':
			N_vectors++;		
			break;
		case 'r':
			N_rays++;		
			break;
		case 'p':
			N_planes++;		
			break;
		case 's':
			N_spheres++;		
			break;
		default:
			fprintf(stderr, "Wrong specification for collection: %s\n",
					specification);
			fprintf(stderr, "Only use characters 'v', 'r', 'p', 's' in this ");
			fprintf(stderr, "order and without whitespaces.\n");
			break;
		}
	}

	// allocate collection structure and fill it
	
	collection *bunch = collection_alloc(N_vectors, N_rays, N_planes,
			N_spheres);

	va_list argp;
	va_start(argp, specification);

	for (int i = 0; i < N_vectors; i++)
		bunch->vectors[i] = va_arg(argp, vector);

	for (int i = 0; i < N_rays; i++)
		bunch->rays[i] = va_arg(argp, ray);

	for (int i = 0; i < N_planes; i++)
		bunch->planes[i] = va_arg(argp, plane);

	for (int i = 0; i < N_spheres; i++)
		bunch->spheres[i] = va_arg(argp, sphere);

	va_end(argp);

	return bunch;
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

void print_geogebra(char *filename, collection *bunch) {

	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		fprintf(stderr, "Error opening file %s.\n", filename);
		return;
	}

	fprintf(file, "Execute[{");

	int N_total = bunch->N_vectors + bunch->N_rays + bunch->N_planes +
			bunch->N_spheres;
	int counter = 0;

	// plot vectors
	
	for (int i = 0; i < bunch->N_vectors; i++) {
		fprintf(file, "\"Vector((0,0,0),(%f,%f,%f))\"",
				bunch->vectors[i].x, bunch->vectors[i].y, bunch->vectors[i].z);
		if (++counter < N_total)
			fprintf(file, ", ");
	}

	// plot rays
	
	for (int i = 0; i < bunch->N_rays; i++) {
		fprintf(file, "\"Line((%f,%f,%f),Vector((0,0,0),(%f,%f,%f)))\"",
				bunch->rays[i].origin.x, bunch->rays[i].origin.y,
				bunch->rays[i].origin.z, bunch->rays[i].direction.x,
				bunch->rays[i].direction.y, bunch->rays[i].direction.z);
		if (++counter < N_total)
			fprintf(file, ", ");
	}
	
	// plot planes
	
	for (int i = 0; i < bunch->N_planes; i++) {
		fprintf(file, "\"PerpendicularPlane((%f,%f,%f),Vector((0,0,0),(%f,%f,%f)))\"",
				bunch->planes[i].origin.x, bunch->planes[i].origin.y,
				bunch->planes[i].origin.z, bunch->planes[i].normal.x,
				bunch->planes[i].normal.y, bunch->planes[i].normal.z);
		if (++counter < N_total)
			fprintf(file, ", ");
	}

	// plot spheres
	
	for (int i = 0; i < bunch->N_spheres; i++) {
		fprintf(file, "\"Sphere((%f,%f,%f),%f)\"",
				bunch->spheres[i].center.x, bunch->spheres[i].center.y,
				bunch->spheres[i].center.z, bunch->spheres[i].radius);
		if (++counter < N_total)
			fprintf(file, ", ");
	}

	fprintf(file, "}]\n");

	fclose(file);
}

intersection intersect_ray_ray(const ray *g, const ray *h) {

	intersection result;

	//checks for collinearity of the direction vectors
	if(are_collinear(g->direction, h->direction)) {

		/* If the rays are identical, both origin vectors point on the same ray.
		 * This means that their difference must be collinear to the direction vector */
		if(are_collinear(g->direction, subtract(g->origin, h->origin))){

			result.kind = contained;

		} else {

			result.kind = parallel;

		}

	} else {
		// create auxiliary plane containing h and being orthogonal to g
		vector direction_2 = cross(g->direction, h->direction);
		plane hplane = plane_assign_parametric(h->origin, h->direction, direction_2);

		// finding parameter value of g at intersection with the auxiliary plane
		// coeff * r = rhs, "right-hand side"
		double coeff = dot(hplane.normal, g->direction);
		double rhs = hplane.d - dot(hplane.normal, g->origin);
		double r = rhs / coeff;

		// the intersection between the ray g and the plane hplane derived from the ray h
		point planeintersection = add(g->origin, multiply(g->direction, r));
			
		// check if intersection lies on the ray h, i.e.
		// if the difference between it and h's origin is parallel to h's direction
		vector diff = connect(h->origin, planeintersection);

		if(are_collinear(diff, h->direction)) {

			result.kind = intersecting;
			result.P = planeintersection;
			result.r = r;

		} else {

			result.kind = skew;

		}

	}

	return result;

}

intersection intersect_ray_plane(const ray *g, const plane *E) {

	intersection result;

	if(are_orthogonal(g->direction, E->normal)) {

		if(are_orthogonal(subtract(E->origin, g->origin), E->normal)) {

			result.kind = contained;

		} else {

			result.kind = parallel;

		}

	} else {

		result.kind = intersecting;

		// finding parameter value of g at intersection with the auxiliary plane
		// coeff * r = rhs, "right-hand side"
		double coeff = dot(E->normal, g->direction);
		double rhs = E->d - dot(E->normal, g->origin);; // srsly how should I name this variable?
		result.r = rhs / coeff;

		result.P = add(g->origin, multiply(g->direction, result.r));

	}

	return result;

}

intersection intersect_ray_sphere(const ray *g, const sphere *S) {

	intersection result;

	vector d = subtract(g->origin, S->center);

	double a = dot(g->direction, g->direction);
	double b = 2 * dot(g->direction, d);
	double c = dot(d, d) - S->radius;

	double discrimant = b * b - 4 * a * c;

	if(discrimant < 0.0) {

		result.kind = none;

	} else {

		result.kind = intersecting;

		result.r = (-b - sqrt(discrimant)) / (2 * a);
		result.r_2 = (-b + sqrt(discrimant)) / (2 * a);

		result.P = add(g->origin, multiply(g->direction, result.r));
		result.P_2 = add(g->origin, multiply(g->direction, result.r_2));

	}

	return result;

}

void intersection_print_ray_ray(const intersection *I, int places) {

	switch(I->kind) {

		case 0: printf("Intersection at %s, ray parameter r = %f\n", vector_print(I->P, places), I->r); break;
		case 1: printf("Parallel, no intersection\n"); break;
		case 2: printf("Skew, no intersection\n"); break;
		case 3: printf("Contained\n"); break;

	}

}

void intersection_print_ray_plane(const intersection *I, int places) {

	switch(I->kind) {

		case 0: printf("Intersection at %s, ray parameter r = &f\n", vector_print(I->P, places), I->r); break;
		case 1: printf("Parallel, no intersection\n"); break;
		case 3: printf("Contained\n"); break;

	}

}

void intersection_print_ray_sphere(const intersection *I, int places) {

	switch(I->kind) {

		case 0: if(I->r == I->r_2) {
				printf("Intersection at %s, ray parameter r = %i\n", vector_print(I->P, places), I->r);
			} else {
				printf("Two intersections at %s and ",vector_print(I->P, places));
				printf("%s, ray parameters r = %f, r_2 = %f\n", vector_print(I->P_2, places), I->r, I->r_2);
			} break;
		case 4: printf("No intersection\n");

	}

}

// Implementation of the functions declared in the header objects.h

