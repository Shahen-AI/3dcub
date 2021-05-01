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
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

struct  	s_data
{
	void    *img;
	char    *addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
}           data;

struct  	s_vars
{
	void    *mlx;
	void    *win;
}           vars;

struct 	s_keys
{
	int down;
	int up;
	int right;
	int left;
} 		keys;

struct s_position
{
	double posX, posY;  //x and y start position
	double dirX , dirY; //initial direction vector
	double planeX, planeY; //the 2d raycaster version of camera plane
}		positions;

int close()
{
	exit(0);
	return 0;
}

int key_press(int keycode)
{
	if(keycode == 0 || keycode == 123) // left or a
		keys.left = 1;
	if(keycode == 1 || keycode == 125) // down or s
		keys.down = 1;
	if(keycode == 2 || keycode == 124) // right or d
		keys.right = 1;
	if(keycode == 13 || keycode == 126) // up or w
		keys.up = 1;

	if (keycode == 53)
	{
		mlx_destroy_window(vars.mlx, vars.win);
		close();
	}
	return 0;
}

int key_release(int keycode)
{
	if(keycode == 0 || keycode == 123) // left or a
		keys.left = 0;
	if(keycode == 1 || keycode == 125) // down or s
		keys.down = 0;
	if(keycode == 2 || keycode == 124) // right or d
		keys.right = 0;
	if(keycode == 13 || keycode == 126) // up or w
		keys.up = 0;
	return 0;
}

unsigned int get_pixel(int x, int y)
{
	unsigned int color;
	char    	*dst;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void            my_mlx_pixel_put(int x, int y, int color)
{
	char    *dst;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		verLine(int x, int drawStart, int drawEnd, int color)
{
	int y = 0;
	int topColor = 0x00ADEAEA;
	int bottomColor = 0x00696969;
	while (y < drawStart)
	{
		my_mlx_pixel_put(x, y, topColor);
		++y;
	}
	while (y < drawEnd)
	{
		my_mlx_pixel_put(x, y, color);
		++y;
	}
	while (y < screenHeight)
	{
		my_mlx_pixel_put(x, y, bottomColor);
		++y;
	}
	return (0);
}

int draw_image()
{
	for(int x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(screenWidth) - 1; //x-coordinate in camera space
		double rayDirX = positions.dirX + positions.planeX * cameraX;
		double rayDirY = positions.dirY + positions.planeY * cameraX;

		//which box of the map we're in
		int mapX = (int)(positions.posX);
		int mapY = (int)(positions.posY);

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
			sideDistX = (positions.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - positions.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (positions.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - positions.posY) * deltaDistY;
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
		if (side == 0) perpWallDist = (mapX - positions.posX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - positions.posY + (1 - stepY) / 2) / rayDirY;

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
			case 1:  color = 0x008B4513; break;
			case 2:  color = 0x00FFF8DC; break;
			case 3:  color = 0x00FFF8DC; break;
			case 4:  color = 0x00FFF8DC; break; 
			default: color = 0x00FFF8DC; break; 
		}

		//give x and y sides different brightness
		if (side == 1) color = color / 2;

		//draw the pixels of the stripe as a vertical line
		verLine(x, drawStart, drawEnd, color);
	}
	return 0;
}

int		key_hook()
{

	double moveSpeed = /*frameTime * */ 0.08; //the constant value is in squares/second
	double rotSpeed = /*frameTime * */ 0.03; //the constant value is in radians/second
	
	// move forward if no wall in front of you
	if (keys.up)
	{
		if(worldMap[(int)(positions.posX + positions.dirX * moveSpeed)][(int)(positions.posY)] == 0)
			positions.posX += positions.dirX * moveSpeed;
		if(worldMap[(int)(positions.posX)][(int)(positions.posY + positions.dirY * moveSpeed)] == 0)
			positions.posY += positions.dirY * moveSpeed;
		draw_image();
	}
	//move backwards if no wall behind you
	if (keys.down)
	{
		if(worldMap[(int)(positions.posX - positions.dirX * moveSpeed)][(int)(positions.posY)] == 0)
			positions.posX -= positions.dirX * moveSpeed;
		if(worldMap[(int)(positions.posX)][(int)(positions.posY - positions.dirY * moveSpeed)] == 0)
			positions.posY -= positions.dirY * moveSpeed;
		draw_image();
	}
	//rotate to the right
	if (keys.right)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = positions.dirX;
		positions.dirX = positions.dirX * cos(-rotSpeed) - positions.dirY * sin(-rotSpeed);
		positions.dirY = oldDirX * sin(-rotSpeed) + positions.dirY * cos(-rotSpeed);
		double oldPlaneX = positions.planeX;
		positions.planeX = positions.planeX * cos(-rotSpeed) - positions.planeY * sin(-rotSpeed);
		positions.planeY = oldPlaneX * sin(-rotSpeed) + positions.planeY * cos(-rotSpeed);
		draw_image();
	}
	//rotate to the left
	if (keys.left)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = positions.dirX;
		positions.dirX = positions.dirX * cos(rotSpeed) - positions.dirY * sin(rotSpeed);
		positions.dirY = oldDirX * sin(rotSpeed) + positions.dirY * cos(rotSpeed);
		double oldPlaneX = positions.planeX;
		positions.planeX = positions.planeX * cos(rotSpeed) - positions.planeY * sin(rotSpeed);
		positions.planeY = oldPlaneX * sin(rotSpeed) + positions.planeY * cos(rotSpeed);
		draw_image();
	}

	return 0;
}

int frame()
{
	mlx_do_sync(vars.mlx);
    key_hook();
    mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
    return (0);
}

int             main(void)
{
	vars.mlx = mlx_init();

	positions.posX = 22; 
	positions.posY = 12;  //x and y start position
	positions.dirX = -1; 
	positions.dirY = 0; //initial direction vector
	positions.planeX = 0;
	positions.planeY = 0.66; //the 2d raycaster version of camera plane

	vars.win  = mlx_new_window(vars.mlx, screenWidth, screenHeight, "Cub3D");
	
	data.img = mlx_new_image(vars.mlx, 1920, 1080);
		
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	draw_image();
	
	mlx_hook(vars.win, 17, 1L << 17, close, 0);
	mlx_hook(vars.win, 2, 1L << 0, key_press, 0);
	mlx_hook(vars.win, 3, 1L << 0, key_release , 0);
	// mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop_hook(vars.mlx, frame, 0);
	mlx_loop(vars.mlx);
}
