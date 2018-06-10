#include "optics.h"

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

// Implementation of the functions declared in optics.h
