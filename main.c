#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define mapWidth 24
#define mapHeight 24
#define screenWidth 1920
#define screenHeight 1080

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
};


typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct  s_vars {
	void        *mlx;
	void        *win;
}               t_vars;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void             key_hook(int keycode, t_vars *vars, void *img)
{
	if (keycode == 0)
		printf("Hello from key_hook!\n");
	else if (keycode == 53)
	{
		// mlx_destroy_image(vars->mlx, img);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(1);
	}
}

int             main(void)
{
	// t_vars  vars;
	// t_data  img;
	// int     img_width;
	// int     img_height;
	// char    *relative_path = "./test.xpm";


	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame
	mlx_new_window(screenWidth, screenHeight, 0, "Raycaster");

	
		for(int x = 0; x < screenWidth; x++)
		{
			//calculate ray position and direction
			double cameraX = 2 * x / (double)(screenWidth) - 1; //x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
	
				//which box of the map we're in
			int mapX = (int)(posX);
			int mapY = (int)(posY);

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			float deltaDistX = fabs(1 / rayDirX);
			float deltaDistY = fabs(1 / rayDirY);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?

			// Alternative code for deltaDist in case division through zero is not supported
			 deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
			 deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));

			//calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}

			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, OR in x-direction, OR in y-direction
				if (sideDistX < sideDistY)
				{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
				}
				else
				{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[mapX][mapY] > 0) hit = 1;
			}

			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(screenHeight / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + screenHeight / 2;
			if(drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + screenHeight / 2;
			if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;

			//choose wall color
			int color;
			switch(worldMap[mapX][mapY])
			{
				case 1:  color = 0x00FF0000;  break; //red
				case 2:  color = 0x0000FF00;  break; //green
				case 3:  color = 0x000000FF;   break; //blue
				case 4:  color = 0x00FFFFFF;  break; //white
				default: color = 0x00FFFF00; break; //yellow
			}

			//give x and y sides different brightness
			if (side == 1) {color = color / 2;}

			//draw the pixels of the stripe as a vertical line
			verLine(x, drawStart, drawEnd, color);
   		}

			//timing for input and FPS counter
		oldTime = time;
		// time = getTicks();
		double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		// print(1.0 / frameTime); //FPS counter
		// redraw();
		// cls();

		//speed modifiers
		double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

		// readKeys();
		//move forward if no wall in front of you
		// if (keyDown(SDLK_UP))
		// {
		// if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0) posX += dirX * moveSpeed;
		// if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
		// }
		// //move backwards if no wall behind you
		// if (keyDown(SDLK_DOWN))
		// {
		// if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == 0) posX -= dirX * moveSpeed;
		// if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
		// }
		// //rotate to the right
		// if (keyDown(SDLK_RIGHT))
		// {
		// //both camera direction and camera plane must be rotated
		// double oldDirX = dirX;
		// dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		// dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		// double oldPlaneX = planeX;
		// planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		// planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		// }
		// //rotate to the left
		// if (keyDown(SDLK_LEFT))
		// {
		// //both camera direction and camera plane must be rotated
		// double oldDirX = dirX;
		// dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		// dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		// double oldPlaneX = planeX;
		// planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		// planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		// }
  


	
	
	
	
	
	
	// vars.mlx = mlx_init();
	// vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	// img.img = mlx_new_image(vars.mlx, 1920, 1080);
	// // img.img = mlx_xpm_file_to_image(vars.mlx, relative_path, &img_width, &img_height);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	//                              &img.endian);
	// int i = -1,j;
	// while (++i < 500)
	// {
	//     j = -1;
	//     while (++j < 500)
	//         my_mlx_pixel_put(&img, j + 400, i + 200, 0x00FA0451);
	// }
	// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 400, 700);
	// mlx_key_hook(vars.win, key_hook, &vars);

	mlx_loop(vars.mlx);
}