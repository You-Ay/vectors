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
	
	/* 
	* Box 
	*/


	//Boden
	vector a_E_1 = vector_assign(0, 0, 0);
	vector u_E_1 = vector_assign(1, 0, 0);
	vector v_E_1 = vector_assign(0, 1, 0);
	plane E_1 = plane_assign_parametric(a_E_1, u_E_1, v_E_1);
	E_1.col= vector_assign(0.511,0.331,0.157);
	E_1.mat= vector_assign(0.8,0.2,0);

	//Decke
	vector a_E_2 = vector_assign(0, 0, 0.3);
	vector u_E_2 = vector_assign(1, 0, 0);
	vector v_E_2 = vector_assign(0, 1, 0);
	plane E_2 = plane_assign_parametric(a_E_2, u_E_2, v_E_2);
	E_2.col= vector_assign(0.511,0.331,0.157);
	E_2.mat= vector_assign(0.8,0.2,0);
	
	//obere Seite
	vector a_E_3 = vector_assign(0, 0, 0);
	vector u_E_3 = vector_assign(1, 0, 0);
	vector v_E_3 = vector_assign(0, 0, 1);
	plane E_3 = plane_assign_parametric(a_E_3, u_E_3, v_E_3);
	E_3.col= vector_assign(1,1,1);
	E_3.mat= vector_assign(0.1,0.9,0);

	//linke Seite
	vector a_E_4 = vector_assign(0, 0, 0);
	vector u_E_4 = vector_assign(0, 1, 0);
	vector v_E_4 = vector_assign(0, 0, 1);
	plane E_4 = plane_assign_parametric(a_E_4, u_E_4, v_E_4);
	E_4.col= vector_assign(1,1,1);
	E_4.mat= vector_assign(0.1,0.9,0);

	//untere Seite
	vector a_E_5 = vector_assign(0, 1, 0);
	vector u_E_5 = vector_assign(1, 0, 0);
	vector v_E_5 = vector_assign(0, 0, 1);
	plane E_5 = plane_assign_parametric(a_E_5, u_E_5, v_E_5);
	E_5.col= vector_assign(1,1,1);
	E_5.mat= vector_assign(0.1,0.9,0);

	//rechte Seite
        vector a_E_6 = vector_assign(0.8, 0, 0);
	vector u_E_6 = vector_assign(0, 1, 0);
	vector v_E_6 = vector_assign(0, 0, 1);
	plane E_6 = plane_assign_parametric(a_E_6, u_E_6, v_E_6);
	E_6.col= vector_assign(1,1,1);
	E_6.mat= vector_assign(0.1,0.9,0);


	//finite surfaces
	vector a_s_1 = vector_assign(0, 0.35, 0);
	vector u_s_1 = vector_assign(-0.2, 0, 0);
	vector v_s_1 = vector_assign(0, 0.15, 0);
	surface s_1 = parallelogram_assign(a_s_1, u_s_1, v_s_1);
	s_1.col= vector_assign(1,1,1);
	s_1.mat= vector_assign(0.1,0.9,0);

	vector a_s_2 = vector_assign(0.6, 0, 0);
	vector u_s_2 = vector_assign(0.2, 0, 0);
	vector v_s_2 = vector_assign(0, 0.2, 0);
	surface s_2 = parallelogram_assign(a_s_2, u_s_2, v_s_2);
	s_2.col= vector_assign(1,1,1);
	s_2.mat= vector_assign(0.1,0.9,0);

	vector a_s_3 = vector_assign(0.35, 0.2, 0);
	vector u_s_3 = vector_assign(-0.1, 0.1, 0);
	vector v_s_3 = vector_assign(0, 0, 0.3);
	surface s_3 = parallelogram_assign(a_s_3, u_s_3, v_s_3);
	s_3.col= vector_assign(1,1,1);
	s_3.mat= vector_assign(0.1,0.9,0);


	vector a_s_4 = vector_assign(0.35, 0.2, 0);
	vector u_s_4 = vector_assign(0.1, 0.1, 0);
	vector v_s_4 = vector_assign(0, 0, 0.3);
	surface s_4 = parallelogram_assign(a_s_4, u_s_4, v_s_4);
	s_4.col= vector_assign(1,1,1);
	s_4.mat= vector_assign(0.1,0.9,0);

	vector a_s_5= vector_assign(0.35, 0.4, 0);
	vector u_s_5 = vector_assign(0.1, -0.1, 0);
	vector v_s_5 = vector_assign(0, 0, 0.3);
	surface s_5 = parallelogram_assign(a_s_5, u_s_5, v_s_5);
	s_5.col= vector_assign(1,1,1);
	s_5.mat= vector_assign(0.1,0.9,0);


	vector a_s_6 = vector_assign(0.35, 0.4, 0);
	vector u_s_6 = vector_assign(-0.1, -0.1, 0);
	vector v_s_6 = vector_assign(0, 0, 0.3);
	surface s_6 = parallelogram_assign(a_s_6, u_s_6, v_s_6);
	s_6.col= vector_assign(1,1,1);
	s_6.mat= vector_assign(0.1,0.9,0);

	vector a_s_7 = vector_assign(0.5, 0.15, 0);
	vector u_s_7 = vector_assign(0, 0.2, 0);
	vector v_s_7 = vector_assign(0, 0, 0.3);
	surface s_7 = parallelogram_assign(a_s_7, u_s_7, v_s_7);
	s_7.col= vector_assign(1,1,1);
	s_7.mat= vector_assign(0.1,0.9,0);

	vector a_s_8 = vector_assign(0.7, 0.15, 0);
	vector u_s_8 = vector_assign(-1.5, 0.1, 0);
	vector v_s_8 = vector_assign(0, 0, 0.3);
	surface s_8 = parallelogram_assign(a_s_8, u_s_8, v_s_8);
	s_8.col= vector_assign(1,1,1);
	s_8.mat= vector_assign(0.1,0.9,0);

	vector a_s_9 = vector_assign(0, 0.8, 0);
	vector u_s_9 = vector_assign(0.2, 0.2, 0);
	vector v_s_9 = vector_assign(0, 0, 0.3);
	surface s_9 = parallelogram_assign(a_s_9, u_s_9, v_s_9);
	s_9.col= vector_assign(1,1,1);
	s_9.mat= vector_assign(0.1,0.9,0);

	vector a_s_10 = vector_assign(0.3, 0.7, 0);
	vector u_s_10 = vector_assign(0, 0.15, 0);
	vector v_s_10 = vector_assign(0, 0, 0.3);
	surface s_10 = parallelogram_assign(a_s_10, u_s_10, v_s_10);
	s_10.col= vector_assign(1,1,1);
	s_10.mat= vector_assign(0.1,0.9,0);

	vector a_s_11 = vector_assign(0.3, 0.85, 0);
	vector u_s_11 = vector_assign(0.2, 0, 0);
	vector v_s_11 = vector_assign(0, 0, 0.3);
	surface s_11 = parallelogram_assign(a_s_11, u_s_11, v_s_11);
	s_11.col= vector_assign(1,1,1);
	s_11.mat= vector_assign(0.1,0.9,0);

	vector a_s_12 = vector_assign(0.3, 0.7, 0);
	vector u_s_12 = vector_assign(0.2, 0.15, 0);
	vector v_s_12 = vector_assign(0, 0, 0.3);
	surface s_12 = parallelogram_assign(a_s_12, u_s_12, v_s_12);
	s_12.col= vector_assign(1,1,1);
	s_12.mat= vector_assign(0.1,0.9,0);

	vector a_s_13 = vector_assign(0.8, 0.4, 0);
	vector u_s_13 = vector_assign(-0.15, 0, 0);
	vector v_s_13 = vector_assign(0, 0, 0.3);
	surface s_13 = parallelogram_assign(a_s_13, u_s_13, v_s_13);
	s_13.col= vector_assign(1,1,1);
	s_13.mat= vector_assign(0.1,0.9,0);

	vector a_s_14 = vector_assign(0.65, 0.4, 0);
	vector u_s_14 = vector_assign(-0.15, 0.1, 0);
	vector v_s_14 = vector_assign(0, 0, 0.3);
	surface s_14 = parallelogram_assign(a_s_14, u_s_14, v_s_14);
	s_14.col= vector_assign(1,1,1);
	s_14.mat= vector_assign(0.1,0.9,0);

	vector a_s_15 = vector_assign(0.5, 0.5, 0);
	vector u_s_15 = vector_assign(0.15, 0.1, 0);
	vector v_s_15 = vector_assign(0, 0, 0.3);
	surface s_15 = parallelogram_assign(a_s_15, u_s_15, v_s_15);
	s_15.col= vector_assign(1,1,1);
	s_15.mat= vector_assign(0.1,0.9,0);

	vector a_s_16 = vector_assign(0.65, 0.6, 0);
	vector u_s_16 = vector_assign(0, 0.25, 0);
	vector v_s_16 = vector_assign(0, 0, 0.3);
	surface s_16 = parallelogram_assign(a_s_16, u_s_16, v_s_16);
	s_16.col= vector_assign(1,1,1);
	s_16.mat= vector_assign(0.1,0.9,0);

	// LED Streifen
	vector a_s_17 = vector_assign(0, 0.1, 0.299);
	vector u_s_17 = vector_assign(0.015, 0, 0);
	vector v_s_17 = vector_assign(0, 0.33, 0);
	surface s_17 = parallelogram_assign(a_s_17, u_s_17, v_s_17);
	s_17.col= vector_assign(1,1,1);
	s_17.mat= vector_assign(0.1,0.9,0);
	s_17.is_light_source=true;

	vector a_s_18 = vector_assign(0.35, 0, 0.299);
	vector u_s_18 = vector_assign(0.165, 0, 0);
	vector v_s_18 = vector_assign(0, 0.015, 0);
	surface s_18 = parallelogram_assign(a_s_18, u_s_18, v_s_18);
	s_18.col= vector_assign(1,1,1);
	s_18.mat= vector_assign(0.1,0.9,0);
	s_18.is_light_source=true;

	vector a_s_19 = vector_assign(0.8, 0.4, 0.299);
	vector u_s_19 = vector_assign(0, -0.015, 0);
	vector v_s_19 = vector_assign(-0.165, 0, 0);
	surface s_19 = parallelogram_assign(a_s_19, u_s_19, v_s_19);
	s_19.col= vector_assign(1,1,1);
	s_19.mat= vector_assign(0.1,0.9,0);
	s_19.is_light_source=true;

	vector a_s_20 = vector_assign(0.2, 1, 0.299);
	vector u_s_20 = vector_assign(0, -0.015, 0);
	vector v_s_20 = vector_assign(0.165, 0, 0);
	surface s_20 = parallelogram_assign(a_s_20, u_s_20, v_s_20);
	s_20.col= vector_assign(1,1,1);
	s_20.mat= vector_assign(0.1,0.9,0);
	s_20.is_light_source=true;



	// some spheres

	vector c_1 = vector_assign(0.75, 0.35, 0.08);
	double r_1 = 0.08;
	sphere S_1 = sphere_assign(c_1, r_1);
	S_1.col= vector_assign(0.9,0.1,0);
	S_1.mat= vector_assign(1, 0, 0);

	
	


	collection *scene = collection_assign("ppppppSssssssssssssssssssss", E_1, E_2, E_3, E_4, E_5, E_6, S_1, s_1, s_2, s_3, s_4, s_5, s_6, s_7, s_8, s_9, s_10, s_11, 
	s_12, s_13, s_14, s_15, s_16, s_17, s_18, s_19, s_20);


	vector cam_origin = vector_assign(0.6, 0.95, 0.1);
	vector cam_direction = vector_assign(-0.05, -0.15, 0.0);
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
 	int samples;
	srand( time(NULL) );

	int choice;

	printf("For live rendering, type 1, for given number of iterations, type 0: ");
   	scanf("%d", &choice);


    	if(choice == 1)
    	{printf("Rendering process started.   ");
	render_live("baum.ppm", &cam, scr, scene, max_interactions);
        }

	if(choice == 0)

	{printf("How many samples? ");
	scanf("%d", &samples);
	printf("Rendering process started.  ");

	render(&cam, scr, scene, max_interactions, samples);
	}


	screen_print_ppm("baum.ppm", scr);

	collection_free(scene);
	screen_free(scr);

	return 0;

}
