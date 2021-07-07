#include "cub3d.h"

int ft_compare(char *str1, char *str2)
{
    int i = 0;
    if (str1 && str2)
    {
        while (i < 7)
        {
            if (str1[i] == str2[i])
                ++i;
            else
                return (0);
        }
        return (1);
    }
    return (0);
}

void ft_screenshot(t_parser *parser)
{
    int bmp;
    int	all_pix;
	int	zero;
	int	pos_pix;
	int	size;

    bmp = open("./screenshot.bmp", O_CREAT | O_RDWR, 0666);

	all_pix = parser->screenWidth * parser->screenHeight * 4 + 54;
	zero = 0;
	pos_pix = 54;
	size = parser->screenWidth * parser->screenHeight;
	write(bmp, "BM", 2);
	write(bmp, &all_pix, 4);
	write(bmp, &zero, 4);
	write(bmp, &pos_pix, 4);
	pos_pix = 40;
	write(bmp, &pos_pix, 4);
	write(bmp, &parser->screenWidth, 4);
	write(bmp, &parser->screenHeight, 4);
	screenshot_norm_one(bmp);
	screenshot_norm_two(bmp, all_pix, zero, size);
	fill_screen(bmp, parser);
}

void	fill_screen(int fd, t_parser *parser)
{
	int i;
	int j;
	int color;

	// parser->data.img = mlx_new_image(vars.mlx, parser->screenWidth, parser->screenHeight);
		
	// parser->data.addr = mlx_get_data_addr(parser->data.img, &parser->data.bits_per_pixel, &parser->data.line_length, &parser->data.endian);

	i = parser->screenHeight;
	while (--i >= 0)
	{
		j = -1;
		while (++j < parser->screenWidth)
		{
			color = get_pixel(j, i, &parser->data);
			write(fd, &color, 4);
		}
	}
	exit(0);
}

void	screenshot_norm_one(int fd)
{
	short	plane;

	plane = 1;
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
}

void	screenshot_norm_two(int fd, int all_pix, int zero, int size)
{
	write(fd, &zero, 4);
	write(fd, &size, 4);
	all_pix = 1000;
	write(fd, &all_pix, 4);
	write(fd, &all_pix, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
}
