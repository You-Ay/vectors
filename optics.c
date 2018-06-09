#include "optics.h"

void reflect(ray *g, vector normal, point P) {

	g->origin = P;

	vector unormal = normalize(normal);
	vector udirection = normalize(g->direction);
	double parameter = 2 * dot(unormal, udirection);

	g->direction = subtract(multiply(unormal, parameter), udirection);

}

// Implementation of the functions declared in optics.h
