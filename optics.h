#ifndef OPTICS_H
#define OPTICS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>
#include "vector.h"
#include "objects.h"

/*
 * INTERACTION OF LIGHT RAYS WITH DIFFERENT MATERIALS
 */

// change the ray g to after the interaction
// a given material; 'normal' is the normal vector to the surface,
// 'P' the interaction point

// a ray is partially absorbed or illuminated:
// the ray color is multiplied by the object's color;
// - for a black absorber, this would be (0, 0, 0) erasing all color,
// - for a red surface, (1, 0, 0) would absorb everything but red,
// - for a light source, e.g. (10, 10, 10) would illumate
void absorb(ray *g, color col);

// mirror materials:
// reflect according to the law of reflection of classical optics,
// cf. en.wikipedia.org/wiki/Specular_reflection
void reflect(ray *g, vector normal, point P);

// paper-like materials:
// scatter stochastically according to Lambert's cosine law,
// cf. en.wikipedia.org/wiki/Lambert's_cosine_law
void scatter(ray *g, vector normal, point P);

// glass materials with a refractive index nrefr:
// refract or reflect according to Snell's law, or, to be more precise,
// the Fresnel equations to also account for reflections,
// cf. en.wikipedia.org/wiki/Fresnel_equations
void refract(ray *g, vector normal, point P, double nrefr);

/*
 * VIRTUAL SCREEN DATA STRUCTURE
 */

typedef struct {
	// number of pixels in each direction
	int pixels_width;
	int pixels_height;

	// physical width and height of virtual screen
	double width;
	double height;

	// RGB value at each pixel, to be filled by the renderer;
	// color array of size pixels_width*pixels_height defining
	// the image: start at upper left corner, fill line by line
	color *pixel_colors;
} screen;

// allocate and create screen structure; choose height such that pixels are
// square-shaped.
screen * screen_assign(double width, int pixels_width, int pixels_height);

// free allocated memory
void screen_free(screen *scr);

// print colors stored in the screen to an image file,
// in portable pixmap file format (PPM)
void screen_print_ppm(char *filename, const screen *scr);

// map a color value between 0.0 and 1.0 (R, G, or B) to
// a 0..255 integer interval, as expected by standard graphics formats;
// use a standard gamma value of 1 / 2.2
int color2int(double col);

/*
 * CAMERA DATA STRUCTURE
 */

typedef struct {
	// the camera is located at a point 'origin' and looks into 'direction'

	point origin;
	vector direction; // direction into which the camera looks
	vector right; // the direction to the right

	// at a certain distance from the camera, and perpendicular to it,
	// there is a virtual screen
	double screen_distance;

	// orthonormal basis for the camera:
	// e_1: direction of the camera,
	// e_2: to the right,
	// e_3: down
	vector e_1, e_2, e_3;
} camera;

camera camera_assign(point origin, vector direction, vector right,
		double screen_distance);

// return the location of a pixel on the virtual screen:
// 'pixel' is the pixel number (from 0 to scr->pixels_width*scr->pixels_height)
// 'subpixel' is one of the four subpixels of each pixel
point pixel_position(const camera *cam, const screen *scr, long pixel,
		int subpixel);

/*
 * RENDERING BY RAY TRACING
 */

// interactions farther away than distance_limit are considered invalid
extern const double distance_limit;

// data structure for the status of a traced ray
typedef enum {
	valid, // OK, go on with next interaction
	illuminated, // the ray has reached a light source (-> take and leave)
	too_far_away, // the ray is far away from the scene (invalid)
	too_many_interactions, // the ray had too many interactions (invalid)
} trace_status;

// trace a ray:
// 1. calculate the next interaction of the ray g with an object in the scene,
// 2. modify g to after the interaction (reflected / scattered / ...),
// 3. update the trace_status
trace_status trace(ray *g, const collection *scene, int N_interactions,
		int max_interactions);

// render an image:
// - 'cam' and 'scr' define the camera and screen objects,
// - 'scene' is the collection of all objects,
// - 'max_interactions' is the maximum number of interactions a ray is allowed
//   to have unless it hits a light source,
// - 'samples' gives the number of rays launched at each subpixel.
// The renderer traces each ray until it has become either illuminated by
// a light source or has become invalid.
void render(camera *cam, screen *scr, collection *scene, int max_interactions,
		int samples);

#endif /* OPTICS_H */

