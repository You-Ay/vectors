#include "optics.h"

const double distance_limit = 1e6;

void absorb(ray *g, color col) {

	g->col.x = col.x * g->col.x;
	g->col.y = col.y * g->col.y;
	g->col.z = col.z * g->col.z;
}

void reflect(ray *g, vector normal, point P) {

	g->origin = P;

	vector unormal = normalize(normal);

	vector udirection = normalize(g->direction);
	double parameter = 2 * dot(unormal, udirection);

	g->direction = subtract(udirection, multiply(unormal, parameter));

}

void scatter(ray *g, vector normal, point P) {

	vector n = normalize(normal);

	if(dot(n, g->direction) > 0.) { // wrong orientation
		n = multiply(n, -1.0);
	}

	// creates a vector "direction" perpendicular to the normal vector
	vector direction;
	if(n.x != 0 || n.y != 0) {

		direction = vector_assign(-n.y, n.x, 0);

	} else {

		direction = vector_assign(0, -n.z, n.y);

	}

	// creates two orthonormal vectors perpendicular to the normal vector
	vector e_1 = normalize(direction);
	vector e_2 = cross(n, e_1);

	double X_1 = (double)rand() / RAND_MAX; // this is sin(theta)
	double X_2 = ((double)rand() / RAND_MAX) * 2. * M_PI; // this is phi

	double sin_theta = X_1;
	double cos_theta = sqrt(1 - sin_theta * sin_theta); // because sin^2 + cos^2 = 1
	double phi = X_2;

	g->origin = P;
	g->direction = add(add(multiply(n , cos_theta), multiply(e_1, cos(phi) * sin_theta)),
			multiply(e_2, sin(phi) * sin_theta));

}

void refract(ray *g, vector normal, point P, double nrefr) {
	/*
	 * ATTENTION: This function should only be used for spheres
	 */

	g->origin = P;

	// Snell's law in vector form, notations from
	// en.wikipedia.org/wiki/Snell's_law

	vector n = normalize(normal);
	vector l = normalize(g->direction);
	
	// refractive indices n_1, n_2,
	// one is = 1 (air / vacuum), the other is = nrefr;
	// we assume that 'normal' points outside the glass-like object
	
	double n_1, n_2;

	if (dot(n, l) > 0.) { // n oriented like l: the ray leaves the glass
		n = multiply(n, -1.); // Wikipedia convention
		n_1 = nrefr;
		n_2 = 1.;	
	} else { // n opposed to l: the ray enters the glass
		n_1 = 1.;
		n_2 = nrefr;
	}

	// reflected ray direction
	
	double cos_1 = - dot(n, l);
	double r = n_1 / n_2;
	vector v_reflect = add(l, multiply(n, 2.*cos_1));

	// refracted ray direction
	
	double radicand = 1. - r*r  * (1. - cos_1*cos_1);

	if (radicand < 0.) { // total reflection
		g->direction = v_reflect;
		return;
	}

	double cos_2 = sqrt(radicand);
	vector v_refract = add(multiply(l, r), multiply(n, r * cos_1 - cos_2));

	// reflectance R according to Fresnel equations, notations from
	// en.wikipedia.org/wiki/Fresnel_equations
	// R is the probability of the ray being reflected,
	// T = 1 - R is the probability of it being trasmitted (reflected)
	
	// s-polarized light
	double R_s = (n_1 * cos_1 - n_2 * cos_2) / (n_1 * cos_1 + n_2 * cos_2);
	R_s *= R_s;

	// p-polarized light
	double R_p = (n_1 * cos_2 - n_2 * cos_1) / (n_1 * cos_2 + n_2 * cos_1);
	R_p *= R_p;

	// take average as actual reflectance: unpolarized light source
	double R = (R_s + R_p) / 2.;

	// decide whether to reflect or transmit:
	// X random from 0 to 1; X <= R: reflect
	
	double X = ((double) rand()) / ((double) RAND_MAX);
	if (X <= R)
		g->direction = v_reflect;
	else
		g->direction = v_refract;
}

screen * screen_assign(double width, int pixels_width, int pixels_height) {
	long N_pixels = ((long) pixels_width) * ((long) pixels_height);

	// allocate memory
	
	screen * scr = malloc(sizeof(screen));
	if (scr == NULL)
		fprintf(stderr, "Allocating memory for virtual screen failed.\n");

	scr->pixel_colors = malloc(N_pixels * sizeof(color));
	if (scr->pixel_colors == NULL)
		fprintf(stderr, "Allocating memory for pixel colors failed.\n");

	// assign values

	scr->pixels_width = pixels_width;
	scr->pixels_height = pixels_height;

	scr->width = width;
	scr->height = width * ((double) pixels_height) / ((double) pixels_width);

	// initialize all color values to black
	for (long i = 0; i < N_pixels; i++)
		scr->pixel_colors[i] = vector_assign(0, 0, 0);

	return scr;
}

void screen_free(screen *scr) {
	free(scr->pixel_colors);
	free(scr);
}

void screen_print_ppm(char *filename, const screen *scr) {
	FILE *f = fopen(filename, "w");
	if (f == NULL) {
		fprintf(stderr, "Could not open file %s\n", filename);
		return;
	}

	// format specifications for PPM file
	fprintf(f, "P3\n");
	fprintf(f, "%d %d\n", scr->pixels_width, scr->pixels_height);
	fprintf(f, "%d\n", 255);

	// write color values to file
	for (long i = 0; i < scr->pixels_width*scr->pixels_height; i++) {
		fprintf(f, "%d ", color2int(scr->pixel_colors[i].x));
		fprintf(f, "%d ", color2int(scr->pixel_colors[i].y));
		fprintf(f, "%d\n", color2int(scr->pixel_colors[i].z));
	}

	fclose(f);
}

int color2int(double col) {
	// cut color value to 0..1 interval
	if (col > 1.)
		col = 1.;
	else if (col < 0.)
		col = 0.;

	// apply gamma correction
	double gamma = 1. / 2.2;
	col = pow(col, gamma);

	// round to integer between 0 and 255
	col *= 255.;
	col += 0.5;

	return ((int) col);
}

camera camera_assign(point origin, vector direction, vector up,
		double screen_distance) {
	camera cam;
	cam.origin = origin;
	cam.direction = direction;
	cam.up = up;
	cam.screen_distance = screen_distance;

	if (!are_orthogonal(cam.direction, cam.up))
		fprintf(stderr, "Camera look and up directions have to be orthogonal.\n");

	// create orthonormal basis for the camera:
	
	cam.e_1 = normalize(cam.direction); // front
	cam.e_3 = normalize(multiply(cam.up, -1.)); // down
	cam.e_2 = cross(cam.e_3, cam.e_1); // right

	return cam;
}

point pixel_position(const camera *cam, const screen *scr, long pixel,
		int subpixel) {

	// calculate screen center and position of upper left corner
	
	point center = add(cam->origin, multiply(cam->e_1, cam->screen_distance));

	point upper_left = subtract(center, multiply(cam->e_2, scr->width / 2.));
	upper_left = subtract(upper_left, multiply(cam->e_3, scr->height / 2.));

	// count how many pixels we have to go the right and down,
	// note that we use integer division
	
	double pixels_down = pixel / scr->pixels_width;
	double pixels_right = pixel - ((long) pixels_down) * ((long) scr->pixels_width);

	// add subpixel correction: move to center of subpixel
	
	switch (subpixel) {
	case 0: // upper left
		pixels_down += 0.25;
		pixels_right += 0.25;
		break;
	case 1: // upper right
		pixels_down += 0.25;
		pixels_right += 0.75;
		break;
	case 2: // lower left
		pixels_down += 0.75;
		pixels_right -= 0.25;
		break;
	case 3: // lower right
		pixels_down += 0.75;
		pixels_right += 0.75;
		break;
	}

	// go this distance to get to the center of the (sub)pixel

	double size = scr->width / ((double) scr->pixels_width);
	point pixel_center = add(upper_left, multiply(cam->e_2, pixels_right*size));
	pixel_center = add(pixel_center, multiply(cam->e_3, pixels_down*size));

	return pixel_center;
}

trace_status trace(ray *g, const collection *scene, int N_interactions,
		int max_interactions) {
	//printf("N_interactions = %d\n", N_interactions);
	//printf("max_interactions = %d\n", max_interactions);
	if (N_interactions >= max_interactions)
		return too_many_interactions;

	double r_plane_min = distance_limit;
	double r_sphere_min = distance_limit;
	double r_triangle_min = distance_limit;
	double r_parallelogram_min = distance_limit;
	int i_plane = -1;
	int i_sphere = -1;
	int i_triangle = -1;
	int i_parallelogram = -1;

	intersection I;

	for (int i = 0; i < scene->N_planes; i++) {
		I = intersect_ray_plane(g, &scene->planes[i]);
		if (I.kind != intersecting)
			continue;
		if (I.r < r_plane_min && I.r > epsilon) {
			i_plane = i;
			r_plane_min = I.r;
		}
	}

	for (int i = 0; i < scene->N_spheres; i++) {
		I = intersect_ray_sphere(g, &scene->spheres[i]);
		if (I.kind != intersecting)
			continue;
		if (I.r < r_sphere_min && I.r > epsilon) {
			i_sphere = i;
			r_sphere_min = I.r;
		}
		if (I.r_2 < r_sphere_min && I.r_2 > epsilon) {
			i_sphere = i;
			r_sphere_min = I.r;
		}
	}

	for (int i = 0; i < scene->N_triangles; i++) {
		I = intersect_ray_triangle(g, &scene->triangles[i]);
		//intersection_print_ray_plane(&I, 1);
		if (I.kind != intersecting)
			continue;
		//intersection_print_ray_plane(&I, 1);
		if (I.r < r_triangle_min && I.r > epsilon) {
			i_triangle = i;
			r_triangle_min = I.r;
		}
	}

	for(int i = 0; i < scene->N_parallelograms; i++) {
		I = intersect_ray_parallelogram(g, &scene->parallelograms[i]);
		if (I.kind != intersecting)
			continue;
		if (I.r < r_parallelogram_min && I.r > epsilon) {
			i_parallelogram = i;
			r_parallelogram_min = I.r;
		}
	}

	if (i_plane == -1 && i_sphere == -1 && i_triangle == -1 && i_parallelogram == -1)
		return too_far_away;

	color col;
	vector normal;
	point P;
	material mat;
	bool is_light_source;

	if (r_plane_min < r_sphere_min && r_plane_min < r_triangle_min && r_plane_min < r_parallelogram_min) {
		col = scene->planes[i_plane].col;
		normal = scene->planes[i_plane].normal;
		P = add(g->origin, multiply(g->direction, r_plane_min));
		mat = scene->planes[i_plane].mat;
		is_light_source = scene->planes[i_plane].is_light_source;
		//printf("Hit plane %d\n", i_plane+1);
	} else if(r_sphere_min < r_triangle_min && r_sphere_min < r_parallelogram_min) {
		col = scene->spheres[i_sphere].col;
		P = add(g->origin, multiply(g->direction, r_sphere_min));
		normal = subtract(P, scene->spheres[i_sphere].center);
		mat = scene->spheres[i_sphere].mat;
		is_light_source = scene->spheres[i_sphere].is_light_source;
		//printf("Hit sphere %d\n", i_sphere+1);
	} else if(r_triangle_min < r_parallelogram_min) {
		col = scene->triangles[i_triangle].col;
		normal = scene->triangles[i_triangle].normal;
		P = add(g->origin, multiply(g->direction, r_triangle_min));
		mat = scene->triangles[i_triangle].mat;
		is_light_source = scene->triangles[i_triangle].is_light_source;
		//printf("Hit triangle %d\n", i_triangle+1);
	} else {
		col = scene->parallelograms[i_parallelogram].col;
		normal = scene->parallelograms[i_parallelogram].normal;
		P = add(g->origin, multiply(g->direction, r_parallelogram_min));
		mat = scene->parallelograms[i_parallelogram].mat;
		is_light_source = scene->parallelograms[i_parallelogram].is_light_source;
		//printf("Hit parallelogram %d\n", i_parallelogram+1);
	}

	absorb(g, col);
	if (is_light_source)
		return illuminated;

	double X = ((double) rand()) / ((double) RAND_MAX);

	if (X <= mat.x)
		scatter(g, normal, P);
	else if (X <= mat.x + mat.y)
		reflect(g, normal, P);
	else
		refract(g, normal, P, 1.5); // hard-coded refractive index
	
	return valid;
}

void render(camera *cam, screen *scr, collection *scene, int max_interactions,
		int samples) {

	time_t clock_start = time(NULL);

	for (int sample = 0; sample < samples; sample++) {
		render_sample(cam, scr, scene, max_interactions);

		double time_passed = (double)(time(NULL) - clock_start);
		double time_togo = time_passed * ((double) samples - ((double) sample+1)) /
				((double) sample+1) + 0.5;
		long T = (long) time_togo;

		int hours = T / 3600;
		int mins = (T - hours * 3600) / 60;
		int secs = T - hours * 3600 - mins * 60;

		printf("Rendered sample %d of %d. ", sample+1, samples);
		printf("About %d h %d min %d sec left.\n", hours, mins, secs);
	}

	// calculate average for each pixel

	unsigned long N_pxls = ((long) scr->pixels_width) * ((long) scr->pixels_height);

	for (long pxl = 0; pxl < N_pxls; pxl++)
		scr->pixel_colors[pxl] = divide(scr->pixel_colors[pxl], ((double) samples));
}

void render_live(char *filename, camera *cam, screen *scr, collection *scene,
		int max_interactions) {

	unsigned long N_pxls = ((long) scr->pixels_width) * ((long) scr->pixels_height);

	// screen for printing to file (stores averages)
	screen * scr_average = screen_assign(scr->width, scr->pixels_width,
			scr->pixels_height);

	long samples = 1;

	while (true) {
		printf("Rendering sample %d > %s\n", samples, filename);
		render_sample(cam, scr, scene, max_interactions);

		for (long pxl = 0; pxl < N_pxls; pxl++)
			scr_average->pixel_colors[pxl] = divide(scr->pixel_colors[pxl],
					((double) samples));


		screen_print_ppm(filename, scr_average);

		samples++;
	}

	screen_free(scr_average);
}

void render_sample(camera *cam, screen *scr, collection *scene,
		int max_interactions) {

	unsigned long N_pxls = ((long) scr->pixels_width) * ((long) scr->pixels_height);

#pragma omp parallel for schedule (dynamic, 1)
	for (long pxl = 0; pxl < N_pxls; pxl++) {
		for (int subpxl = 0; subpxl < 4; subpxl++) {
			point P = pixel_position(cam, scr, pxl, subpxl);
			ray g = ray_assign_points(cam->origin, P);
			g.col = vector_assign(1, 1, 1);
				
			trace_status status;
			int N_interactions = 0;

			do {
				status = trace(&g, scene, N_interactions++, max_interactions);
			} while(status == valid);

			if (status != illuminated)
				continue;

			scr->pixel_colors[pxl] = add(scr->pixel_colors[pxl],
					divide(g.col, 4.));

		}
	}
}

