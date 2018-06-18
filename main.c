#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vector.h"
#include "objects.h"
#include "optics.h"

// Main function: program starts here

int main() {
	/*
	 * SCENE
	 */

	// some plane 
	
	vector a_E_1 = vector_assign(0, 0, 0);
	vector u_E_1 = vector_assign(1, 0, 0);
	vector v_E_1 = vector_assign(0, 1, 0);
	plane E_1 = plane_assign_parametric(a_E_1, u_E_1, v_E_1);
	E_1.col= vector_assign(0.8,0.8,0.8);
	E_1.mat= vector_assign(1,0.0,0);

	vector a_E_2 = vector_assign(0, 0, 0);
	vector u_E_2 = vector_assign(0, 1, 0);
	vector v_E_2 = vector_assign(0, 0, 1);
	plane E_2 = plane_assign_parametric(a_E_2, u_E_2, v_E_2);
	E_2.col= vector_assign(0.2,0.2,0.5);
	E_2.mat= vector_assign(1.0, 0.0,0);

	vector a_E_3 = vector_assign(10, 0, 0);
	vector u_E_3 = vector_assign(0, 1, 0);
	vector v_E_3 = vector_assign(0, 0, 1);
	plane E_3 = plane_assign_parametric(a_E_3, u_E_3, v_E_3);
	E_3.col= vector_assign(0.8,0.2,0.2);
	E_3.mat= vector_assign(1.0,0.,0);

	vector a_E_4 = vector_assign(0, 0, 6);
	vector u_E_4 = vector_assign(1, 0, 0);
	vector v_E_4 = vector_assign(0, 1, 0);
	plane E_4 = plane_assign_parametric(a_E_4, u_E_4, v_E_4);
	E_4.col = vector_assign(0.2, 0.8, 1);
	E_4.is_light_source = true;
	//E_4.col= vector_assign(0.8,0.8,0.8);
	//E_4.mat= vector_assign(0.8,0.2,0);

	vector a_E_5 = vector_assign(0, 10, 0);
	vector u_E_5 = vector_assign(1, 0, 0);
	vector v_E_5 = vector_assign(0, 0, 1);
	plane E_5 = plane_assign_parametric(a_E_5, u_E_5, v_E_5);
	E_5.col= vector_assign(0.2,0.5,0.2);
	E_5.mat= vector_assign(1,0.,0);

	vector a_E_6 = vector_assign(0, -2, 0);
	vector u_E_6 = vector_assign(1, 0, 0);
	vector v_E_6 = vector_assign(0, 0, 1);
	plane E_6 = plane_assign_parametric(a_E_6, u_E_6, v_E_6);
	E_6.col= vector_assign(0.9,0.9,0.8);
	E_6.mat= vector_assign(1,0.,0);
	

	// some spheres
	
	vector c_1 = vector_assign(5, 5, 6);
	double r_1 = 1;
	sphere S_1 = sphere_assign(c_1, r_1);
	S_1.col = vector_assign(10,11,11);
	S_1.is_light_source = true;

	vector c_2 = vector_assign(9, 8, 0.5);
	double r_2 = 0.5;
	sphere S_2 = sphere_assign(c_2, r_2);
	S_2.col = vector_assign(0.7, 0, 0.1);
	S_2.mat = vector_assign(0.5, 0.5, 0);

	vector c_3 = vector_assign(9, 8.2, 1);
	double r_3 = 0.5;
	sphere S_3 = sphere_assign(c_3, r_3);
	S_3.col = vector_assign(0.1, 0.7, 0);	
	S_3.mat = vector_assign(0.5, 0.5, 0);

	vector c_4 = vector_assign(9.2, 8.2, 2);
	double r_4 = 0.5;
	sphere S_4 = sphere_assign(c_4, r_4);
	S_4.col = vector_assign(0.3, 0, 0.6);
	S_4.mat = vector_assign(0.5, 0.5, 0);

	vector c_5 = vector_assign(9.2, 8, 3);
	double r_5 = 0.5;
	sphere S_5 = sphere_assign(c_5, r_5);
	S_5.col = vector_assign(0.5, 0, 0.3);
	S_5.mat = vector_assign(0.5, 0.5, 0);

	vector c_6 = vector_assign(9, 7.8, 4);
	double r_6 = 0.5;
	sphere S_6 = sphere_assign(c_6, r_6);
	S_6.col = vector_assign(0.3, 0.3, 0.3);
	S_6.mat = vector_assign(0.5, 0.5, 0);

	vector c_7 = vector_assign(6, 7, 2);
	double r_7 = 2;
	sphere S_7 = sphere_assign(c_7, r_7);
	S_7.col = vector_assign(0, .6, .6);	
	S_7.mat = vector_assign(0.5, 0.5, 0);

	vector c_8 = vector_assign(2, 7.5, 1.5);
	double r_8 = 1.5;
	sphere S_8 = sphere_assign(c_8, r_8);
	S_8.col = vector_assign(1, 1, 1);
	S_8.mat = vector_assign(0, 1, 0);

	collection *scene = collection_assign("ppppppsssssss", E_1, E_2, E_3, E_4, E_5, E_6,
			S_2, S_3, S_4, S_5, S_6, S_7, S_8);

	vector cam_origin = vector_assign(6.0, 0.0, 2.5);
	vector cam_direction = vector_assign(-0.1, 1.0, 0.0);
	vector cam_up = vector_assign(0.0, 0.0, 1.0);
	double screen_distance = 1.0;

	camera cam = camera_assign(cam_origin, cam_direction, cam_up, screen_distance);

	double width = tan(45.0 * (M_PI / 180.0)) * 2.0;

	double pixel_width = 1280;
	double pixel_height = 1024;
	
	screen *scr = screen_assign(width, pixel_width, pixel_height);

	/*
	 * RENDER AND PRINT
	 */

	int max_interactions = 6;
	int samples = 100;

	srand( time(NULL) );

	render(&cam, scr, scene, max_interactions, samples);

	screen_print_ppm("baum.ppm", scr);

	collection_free(scene);
	screen_free(scr);

	return 0;

}
