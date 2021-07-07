#include "cub3d.h"

int cub_close()
{
	exit(0);
	return 0;
}

int key_press(int keycode)
{
	if(keycode == 123)
		keys.rotLeft = 1;
	if(keycode == 0)
		keys.left = 1;
	if(keycode == 2)
		keys.right = 1;
	if(keycode == 1)
		keys.down = 1;
	if(keycode == 124)
		keys.rotRight = 1;
	if(keycode == 13)
		keys.up = 1;
	if(keycode == 48)
		keys.tab = 1;
	if(keycode == 257)
		keys.shift = 1;
	if (keycode == 53)
	{
		mlx_destroy_window(vars.mlx, vars.win);
		cub_close();
	}
	return 0;
}

int key_release(int keycode)
{
	if(keycode == 123)
		keys.rotLeft = 0;
	if(keycode == 0)
		keys.left = 0;
	if(keycode == 2)
		keys.right = 0;
	if(keycode == 1)
		keys.down = 0;
	if(keycode == 124)
		keys.rotRight = 0;
	if(keycode == 13)
		keys.up = 0;
	if(keycode == 48)
		keys.tab = 0;
	if(keycode == 257)
		keys.shift = 0;
	return 0;
}

unsigned int get_pixel(int x, int y, t_data *dataTex)
{
	unsigned int 	color;
	char   	*dst;

	dst = dataTex->addr + (y * dataTex->line_length + x * (dataTex->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void            my_mlx_pixel_put(int x, int y, int color, t_parser* parser)
{
	char    *dst;

	dst = parser->data.addr + (y * parser->data.line_length + x * (parser->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int draw_image(t_parser *parser)
{
	double ZBuffer[parser->screenWidth];
	for(int x = 0; x < parser->screenWidth; x++)
	{
		double cameraX = 2 * x / (double)(parser->screenWidth) - 1;
		double rayDirX = positions.dirX + positions.planeX * cameraX;
		double rayDirY = positions.dirY + positions.planeY * cameraX;

		int mapX = (int)(positions.posX);
		int mapY = (int)(positions.posY);

		double sideDistX;
		double sideDistY;

		float deltaDistX = fabs(1 / rayDirX);
		float deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));

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

		while (hit == 0)
		{
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
			if (parser->WorldMap[mapX][mapY] == '1') hit = 1;
		}

		if (side == 0) perpWallDist = (mapX - positions.posX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - positions.posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(parser->screenHeight / perpWallDist);

		int drawStart = -lineHeight / 2 + parser->screenHeight / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + parser->screenHeight / 2;
		if(drawEnd >= parser->screenHeight)drawEnd = parser->screenHeight - 1;

		int color;
		int y = 0;
		while (y < drawStart)
		{
			my_mlx_pixel_put(x, y, parser->topColor, parser);
			++y;
		}
		double WallX;
		if (side == 0)
			WallX = positions.posY + perpWallDist * rayDirY;
		else WallX = positions.posX + perpWallDist * rayDirX;
		WallX -= floor(WallX);
		int texX = (int)(WallX * (double)texWidth);
		if (side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if (side && rayDirY < 0) texX = texWidth - texX - 1;
		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - parser->screenHeight / 2 + lineHeight / 2) * step;
		for (y = drawStart; y<drawEnd; y++)
		{
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			if (side == 0)
			{
				if (stepX > 0)
					color = get_pixel(texX, texY, &parser->dataTexN);
				else
					color = get_pixel(texX, texY, &parser->dataTexS);
			}
			else
			{
				if (stepY > 0)
					color = get_pixel(texX, texY, &parser->dataTexW);
				else
					color = get_pixel(texX, texY, &parser->dataTexE);
			}
			if(side == 1) color = (color >> 1) & 8355711;
			my_mlx_pixel_put(x, y, color, parser);
		}
		while (y < parser->screenHeight)
		{
			my_mlx_pixel_put(x, y, parser->bottomColor, parser);
			++y;
		}
		ZBuffer[x] = perpWallDist;
	}
	for(int i = 0; i < parser->sprites.count; i++)
    {
        parser->sprites.sprites[i]->distance = ((positions.posX - parser->sprites.sprites[i]->x)
		* ((positions.posX - parser->sprites.sprites[i]->x) + (positions.posY - parser->sprites.sprites[i]->y)
		* (positions.posY - parser->sprites.sprites[i]->y)));
    }
    sort_sprites(parser);
    for(int i = 0; i < parser->sprites.count; i++)
    {
        double spriteX = parser->sprites.sprites[i]->x - positions.posX + 0.5;
        double spriteY = parser->sprites.sprites[i]->y - positions.posY + 0.5;

        double invDet = 1.0 / (positions.planeX * positions.dirY - positions.dirX * positions.planeY); 

        double transformX = invDet * (positions.dirY * spriteX - positions.dirX * spriteY);
        double transformY = invDet * (-positions.planeY * spriteX + positions.planeX * spriteY); 

        int spriteScreenX = (int)((parser->screenWidth / 2) * (1 + transformX / transformY));

        int spriteHeight = abs((int)(parser->screenHeight / (transformY)));

        int drawStartY = -spriteHeight / 2 + parser->screenHeight / 2;
        if(drawStartY < 0) drawStartY = 0;
        int drawEndY = spriteHeight / 2 + parser->screenHeight / 2;
        if(drawEndY >= parser->screenHeight) drawEndY = parser->screenHeight - 1;

        int spriteWidth = abs((int)(parser->screenHeight / (transformY)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if(drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if(drawEndX >= parser->screenWidth) drawEndX = parser->screenWidth - 1;
        for(int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
            if(transformY > 0 && stripe > 0 && stripe < parser->screenWidth && transformY < ZBuffer[stripe])
            {
                for(int y = drawStartY; y < drawEndY; y++) 
                {
                    int d = (y) * 256 - parser->screenHeight * 128 + spriteHeight * 128;
                    int texY = ((d * texHeight) / spriteHeight) / 256;
                    if (get_pixel(texX, texY, &parser->dataSpr))
                        my_mlx_pixel_put(stripe, y,  get_pixel(texX, texY, &parser->dataSpr), parser);
                }
            }
        }
    }
	return 0;
}

int		key_hook(t_parser *parser)
{
	double moveSpeed = 0.07;
	double rotSpeed = 0.03;

	if(keys.shift)
		moveSpeed *= 2;
	if (keys.up)
	{
		if(parser->WorldMap[(int)(positions.posX + positions.dirX * moveSpeed)][(int)(positions.posY)] == '0')
			positions.posX += positions.dirX * moveSpeed;
		if(parser->WorldMap[(int)(positions.posX)][(int)(positions.posY + positions.dirY * moveSpeed)] == '0')
			positions.posY += positions.dirY * moveSpeed;
	}
	if (keys.down)
	{
		if(parser->WorldMap[(int)(positions.posX - positions.dirX * moveSpeed)][(int)(positions.posY)] == '0')
			positions.posX -= positions.dirX * moveSpeed;
		if(parser->WorldMap[(int)(positions.posX)][(int)(positions.posY - positions.dirY * moveSpeed)] == '0')
			positions.posY -= positions.dirY * moveSpeed;
	}
	
	if (parser->NSWEcheck == 1)
	{
		if (keys.left)
		{
			if(parser->WorldMap[(int)(positions.posX + positions.dirY * moveSpeed)][(int)(positions.posY)] == '0')
				positions.posX += positions.dirY * moveSpeed;
			if(parser->WorldMap[(int)(positions.posX)][(int)(positions.posY - positions.dirX * moveSpeed)] == '0')
				positions.posY -= positions.dirX * moveSpeed;
		}
		if (keys.right)
		{
			if(parser->WorldMap[(int)(positions.posX - positions.dirY * moveSpeed)][(int)(positions.posY)] == '0')
				positions.posX -= positions.dirY * moveSpeed;
			if(parser->WorldMap[(int)(positions.posX)][(int)(positions.posY + positions.dirX * moveSpeed)] == '0')
				positions.posY += positions.dirX * moveSpeed;
		}
		if (keys.rotLeft)
		{
			double oldDirX = positions.dirX;
			positions.dirX = positions.dirX * cos(-rotSpeed) - positions.dirY * sin(-rotSpeed);
			positions.dirY = oldDirX * sin(-rotSpeed) + positions.dirY * cos(-rotSpeed);
			double oldPlaneX = positions.planeX;
			positions.planeX = positions.planeX * cos(-rotSpeed) - positions.planeY * sin(-rotSpeed);
			positions.planeY = oldPlaneX * sin(-rotSpeed) + positions.planeY * cos(-rotSpeed);
		}
		if (keys.rotRight)
		{
			double oldDirX = positions.dirX;
			positions.dirX = positions.dirX * cos(rotSpeed) - positions.dirY * sin(rotSpeed);
			positions.dirY = oldDirX * sin(rotSpeed) + positions.dirY * cos(rotSpeed);
			double oldPlaneX = positions.planeX;
			positions.planeX = positions.planeX * cos(rotSpeed) - positions.planeY * sin(rotSpeed);
			positions.planeY = oldPlaneX * sin(rotSpeed) + positions.planeY * cos(rotSpeed);
		}
	}
	else
	{
		if (keys.right)
		{
			if(parser->WorldMap[(int)(positions.posX + positions.dirY * moveSpeed)][(int)(positions.posY)] == '0')
				positions.posX += positions.dirY * moveSpeed;
			if(parser->WorldMap[(int)(positions.posX)][(int)(positions.posY - positions.dirX * moveSpeed)] == '0')
				positions.posY -= positions.dirX * moveSpeed;
		}
		if (keys.left)
		{
			if(parser->WorldMap[(int)(positions.posX - positions.dirY * moveSpeed)][(int)(positions.posY)] == '0')
				positions.posX -= positions.dirY * moveSpeed;
			if(parser->WorldMap[(int)(positions.posX)][(int)(positions.posY + positions.dirX * moveSpeed)] == '0')
				positions.posY += positions.dirX * moveSpeed;
		}
		if (keys.rotRight)
		{
			double oldDirX = positions.dirX;
			positions.dirX = positions.dirX * cos(-rotSpeed) - positions.dirY * sin(-rotSpeed);
			positions.dirY = oldDirX * sin(-rotSpeed) + positions.dirY * cos(-rotSpeed);
			double oldPlaneX = positions.planeX;
			positions.planeX = positions.planeX * cos(-rotSpeed) - positions.planeY * sin(-rotSpeed);
			positions.planeY = oldPlaneX * sin(-rotSpeed) + positions.planeY * cos(-rotSpeed);
		}
		if (keys.rotLeft)
		{
			double oldDirX = positions.dirX;
			positions.dirX = positions.dirX * cos(rotSpeed) - positions.dirY * sin(rotSpeed);
			positions.dirY = oldDirX * sin(rotSpeed) + positions.dirY * cos(rotSpeed);
			double oldPlaneX = positions.planeX;
			positions.planeX = positions.planeX * cos(rotSpeed) - positions.planeY * sin(rotSpeed);
			positions.planeY = oldPlaneX * sin(rotSpeed) + positions.planeY * cos(rotSpeed);
		}
	}
	return 0;
}

int frame(t_parser* parser)
{
    key_hook(parser);
	mlx_clear_window(vars.mlx, vars.win);

	draw_image(parser);
    mlx_put_image_to_window(vars.mlx, vars.win, parser->data.img, 0, 0);
	mlx_do_sync(vars.mlx);
    return (0);
}

void	parser_init(t_parser *parser)
{
	parser->screenHeight = 0;
	parser->screenWidth = 0;
	parser->topColor = 0;
	parser->bottomColor = 0;
	parser->NOcheck = 0;
	parser->SOcheck = 0;
	parser->EAcheck = 0;
	parser->WEcheck = 0;
	parser->Ccheck = 0;
	parser->Scheck = 0;
	parser->Fcheck = 0;
	parser->Rcheck = 0;
	parser->mapMaxLine = 0;
	parser->mapLineCount = 0;
	parser->NSWEcount = 0;
	parser->sprites.count = 0;
}

int             main(int argc, char **argv)
{
	vars.mlx = mlx_init();
	t_parser parser;
	parser_init(&parser);
	ft_parser(&parser, argv[1]);
	init_sprites(&parser);

	vars.win  = mlx_new_window(vars.mlx, parser.screenWidth, parser.screenHeight, "Cub3D");
	parser.data.img = mlx_new_image(vars.mlx, parser.screenWidth, parser.screenHeight);
		
	parser.data.addr = mlx_get_data_addr(parser.data.img, &parser.data.bits_per_pixel, &parser.data.line_length, &parser.data.endian);

	int wN, hN;
	parser.dataTexN.img = mlx_xpm_file_to_image(vars.mlx, parser.texNpath, &wN, &hN);
	parser.dataTexN.addr = mlx_get_data_addr(parser.dataTexN.img, &parser.dataTexN.bits_per_pixel, &parser.dataTexN.line_length, &parser.dataTexN.endian);

	int wS, hS;
	parser.dataTexS.img = mlx_xpm_file_to_image(vars.mlx, parser.texSpath, &wS, &hS);
	parser.dataTexS.addr = mlx_get_data_addr(parser.dataTexS.img, &parser.dataTexS.bits_per_pixel, &parser.dataTexS.line_length, &parser.dataTexS.endian);

	int wE, hE;
	parser.dataTexE.img = mlx_xpm_file_to_image(vars.mlx, parser.texEpath, &wE, &hE);
	parser.dataTexE.addr = mlx_get_data_addr(parser.dataTexE.img, &parser.dataTexE.bits_per_pixel, &parser.dataTexE.line_length, &parser.dataTexE.endian);

	int wW, hW;
	parser.dataTexW.img = mlx_xpm_file_to_image(vars.mlx, parser.texWpath, &wW, &hW);
	parser.dataTexW.addr = mlx_get_data_addr(parser.dataTexW.img, &parser.dataTexW.bits_per_pixel, &parser.dataTexW.line_length, &parser.dataTexW.endian);

	int wSpr, hSpr;
	parser.dataSpr.img = mlx_xpm_file_to_image(vars.mlx, parser.spritePath, &wSpr, &hSpr);
	parser.dataSpr.addr = mlx_get_data_addr(parser.dataSpr.img, &parser.dataSpr.bits_per_pixel, &parser.dataSpr.line_length, &parser.dataSpr.endian);

	if (argc == 1)
	{
		printf("Please enter a map file!\n");
		cub_close();
	}
	if (argc > 3)
	{
		printf("Too many arguments!\n");
		cub_close();
	}
	if (ft_compare(argv[2], "--save"))
	{
		draw_image(&parser);
		ft_screenshot(&parser);
		cub_close();
	}
	else if (argc == 3)
	{
		printf("Second argument error!!!\n");
		cub_close();
	}
	mlx_hook(vars.win, 17, 1L << 17, cub_close, 0);
	mlx_hook(vars.win, 2, 1L << 0, key_press, 0);
	mlx_hook(vars.win, 3, 1L << 0, key_release , 0);
	mlx_loop_hook(vars.mlx, frame, &parser);
	mlx_loop(vars.mlx);
}
