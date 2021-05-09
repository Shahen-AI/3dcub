#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1920
#define screenHeight 1080
#define texHeight 64
#define texWidth 64



struct  	s_data
{
	void    *img;
	char    *addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
}           data;

struct		s_dataTex
{
	void    *imgTex;
	char    *addrTex;
	int     bits_per_pixel_tex;
	int     line_length_tex;
	int     endianTex;
}           dataTex;

struct  	s_vars
{
	void    *mlx;
	void    *win;
}           vars;

struct 	s_keys
{
	int down;
	int up;
	int rotRight;
	int rotLeft;
	int left;
	int right;
} 		keys;

struct s_position
{
	double posX, posY;  //x and y start position
	double dirX , dirY; //initial direction vector
	double planeX, planeY; //the 2d raycaster version of camera plane
}		positions;


#endif