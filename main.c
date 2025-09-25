#include <stdio.h>
#include <math.h>

int	main(void)
{
	double	cameraX;
	int w = 16;

	//double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	for (int i = 0; i < w; i++) {
		cameraX = 2 * i / (double)w - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		printf ("%.3f\n", cameraX);
		// printf ("rayDirX = %.3f\n", rayDirX);
		// printf ("%.3f\n", rayDirY);

	}



	return (0);
}