#ifndef CUB3D_H
#define CUB3D_H

#include "libs/libft/libft.h"
#include "libs/minilibx_mms/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gnl/get_next_line.h"
#include <fcntl.h>

#define texHeight 64
#define texWidth 64

typedef struct  	s_data
{
	void    *img;
	char    *addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
}           t_data;

typedef struct s_spr_atr
{
	int x;
	int y;
	int distance;
}				t_spr_atr;

typedef struct s_sprites
{
	int count;
	t_spr_atr **sprites;
}				t_sprites;


typedef struct 	s_parser
{
	int topColor;
	int bottomColor;
	int screenWidth;
	int screenHeight;
	char *texNpath;
	char *texSpath;
	char *texWpath;
	char *texEpath;
	char *spritePath;
	t_data data;
	t_data dataTexN;
	t_data dataTexW;
	t_data dataTexE;
	t_data dataTexS;
	t_data dataSpr;
	int NOcheck;
	int SOcheck;
	int EAcheck;
	int WEcheck;
	int Rcheck;
	int Fcheck;
	int Ccheck;
	int Scheck;
	int mapLineCount;
	int mapMaxLine;
	char **WorldMap;
	int NSWEcheck;
	int NSWEcount;
	t_sprites sprites;
}				t_parser;

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
	int shift;
	int tab;
} 		keys;

struct s_position
{
	double posX, posY;  //x and y start position
	double dirX , dirY; //initial direction vector
	double planeX, planeY; //the 2d raycaster version of camera plane
}		positions;

int ft_parser(t_parser *parser, char *path);
int cub_close();
int draw_image(t_parser *parser);
int	key_hook();
int frame(t_parser* parser);
void sort_sprites(t_parser *parser);
void bubble_sort(t_parser *parser);
void init_sprites(t_parser *parser);
void fill_sprites(t_parser *parser);
int ft_compare(char *str1, char *str2);
void ft_screenshot(t_parser *parser);
unsigned int get_pixel(int x, int y, t_data *dataTex);
void	fill_screen(int fd, t_parser *parser);
void	screenshot_norm_one(int fd);
void	screenshot_norm_two(int fd, int all_pix, int zero, int size);

#endif