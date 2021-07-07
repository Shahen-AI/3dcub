#include "cub3d.h"

int is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int rgb2hex(int r, int g, int b)
{
	int res;
	res = (r << 16 | g << 8 | b );
	return (res);
}

int is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char *path_checker(char *line, int i)
{
	char *path;
	int counter = 0, index;
	i += 2;
	while (line[i] && is_space(line[i]))
		++i;
	index = i;
	while (line[i])
	{
		++counter;
		++i;
	}
	i = index;
	index = 0;
	if (!(path = malloc(counter + 1)))
		return (0);
	while (line[i])
	{
		path[index] = line[i];
		++i;
		++index;
	}
	path[index] = '\0';
	int a = open(path, 0666);
	if (a < 0)
	{
		printf("Invalid texture path, please try again!!!");
		cub_close();
	}
	if (!(path[ft_strlen(path) - 1] == 'm' && path[ft_strlen(path) - 2] == 'p' 
		&& path[ft_strlen(path) - 3] == 'x' && path[ft_strlen(path) - 4] == '.'))
	{
		printf("You should put a xpm file!!!");
		cub_close();
	}
	close(a);
	return (path);
}

int ft_colors(char *line, int i)
{
	int res;
	int r = 0 , g = 0 ,b = 0;
	++i;
	while (line[i] && is_space(line[i]))
		++i;
	while (line[i] && is_num(line[i]))
	{
		r = r * 10 + (line[i] - '0');
		++i;
	}
	if (line[i] == ',')
		++i;
	while (line[i] && is_num(line[i]))
	{
		g = g * 10 + (line[i] - '0');
		++i;
	}
	if (line[i] == ',')
		++i;
	while (line[i] && is_num(line[i]))
	{
		b = b * 10 + (line[i] - '0');
		++i;
	}
	if (line[i] != '\0')
	{
		printf("There are some shit after rgb!!!");
		cub_close();
	}
	res = rgb2hex(r, g, b);
	return (res);
}

int filechecker(t_parser *parser)
{
	if (parser->NOcheck == 1 && parser->SOcheck == 1 && parser->EAcheck == 1 && parser->WEcheck == 1
		 && parser->Scheck == 1 && parser->Fcheck == 1 && parser->Ccheck == 1 && parser->Rcheck == 1)
		 	return (1);
	printf("Invalid map file!!!");
	cub_close();
	return (0);
}

int ft_mappars(char *line, t_parser *parser, int number)
{
	int i = 0;
	while (line[i])
	{
		if (!is_space(line[i]) && (line[i] == '1' || line[i] == '0' || line[i] == '2'
			|| line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E'))
			parser->WorldMap[number][i] = line[i];
		else if (is_space(line[i]));
		else
		{
			printf("Shit detected - %c!!!\n", line[i]);
			cub_close();
		}
		if(parser->WorldMap[number][i] == 'N' || parser->WorldMap[number][i] == 'S'
			|| parser->WorldMap[number][i] == 'W' || parser->WorldMap[number][i] == 'E')
		{
			positions.posX = number + 0.5;
			positions.posY = i + 0.5;
			if (parser->WorldMap[number][i] == 'S')
			{
				positions.dirX = 1;
				positions.dirY = 0;
				positions.planeX = 0;
				positions.planeY = 0.66;
			}
			else if (parser->WorldMap[number][i] == 'N')
			{
				positions.dirX = -1;
				positions.dirY = 0;
				positions.planeX = 0;
				positions.planeY = -0.66;
			}
			else if (parser->WorldMap[number][i] == 'W')
			{
				positions.dirX = 0;
				positions.dirY = -1;
				positions.planeX = -0.66;
				positions.planeY = 0;
			}
			else
			{
				positions.dirX = 0;
				positions.dirY = 1;
				positions.planeX = 0.66;
				positions.planeY = 0;
			}
			if (parser->WorldMap[number][i] == 'S' || parser->WorldMap[number][i] == 'N')
				parser->NSWEcheck = 1;
			++parser->NSWEcount;
			parser->WorldMap[number][i] = '0';
		}
		if (parser->WorldMap[number][i] == '2')
			++parser->sprites.count;
		++i;
	}
	return (0);
}

void map_init(int x, int y, t_parser *parser)
{
	int i = -1;
	parser->WorldMap = malloc((y + 1) * sizeof(char *));
	while (++i < y)
		parser->WorldMap[i] = malloc((x + 1) * sizeof(char *));
	parser->WorldMap[i] = NULL;
	int j = 0;
	while (j < y)
	{
		i = 0;
		while (i < x)
		{
			parser->WorldMap[j][i] = '*';
			++i;
		}
		parser->WorldMap[j][i] = '\0';
		++j;
	}
}

int final_pars(t_parser *parser)
{
	int i, j = 0;
	while (j < parser->mapMaxLine)
	{
		if (!((parser->WorldMap[0][j] == '*' || parser->WorldMap[0][j] == '1')
		&& (parser->WorldMap[parser->mapLineCount - 1][j] == '*' || parser->WorldMap[parser->mapLineCount - 1][j] == '1')))
		{
			printf("Map is invalid!!!\n");
			cub_close();
		}
		if (parser->WorldMap[0][j] == '*')
		{
			if (!(parser->WorldMap[1][j] == '*' || parser->WorldMap[1][j] == '1'))
			{
				printf("There are zeros in the walls\n");
				cub_close();
			}
		}
		if (parser->WorldMap[parser->mapLineCount - 1][j] == '*')
		{
			if (!((parser->WorldMap[parser->mapLineCount - 2][j] == '*' || parser->WorldMap[parser->mapLineCount - 2][j] == '1')))
			{
				printf("There are zeros in the walls\n");
				cub_close();
			}
		}
		++j;
	}
	j = 0;
	while (j < parser->mapLineCount)
	{
		if (!((parser->WorldMap[j][0] == '*' || parser->WorldMap[j][0] == '1')
		&& (parser->WorldMap[j][parser->mapMaxLine - 1] == '*' || parser->WorldMap[j][parser->mapMaxLine - 1] == '1')))
		{
			printf("Map is invalid!!!\n");
			cub_close();
		}
		if (parser->WorldMap[j][0] == '*')
		{
			if (!((parser->WorldMap[j][1] == '*' || parser->WorldMap[j][1] == '1')))
			{
				printf("There are zeros in the walls\n");
				cub_close();
			}
		}
		if (parser->WorldMap[j][parser->mapMaxLine - 1] == '*')
		{
			if (!(parser->WorldMap[j][parser->mapMaxLine - 2] == '*' || parser->WorldMap[j][parser->mapMaxLine - 2] == '1'))
			{
				printf("There are zeros in the walls\n");
				cub_close();
			}
		}
		++j;
	}
	j = 1;
	while (j < parser->mapLineCount - 1)
	{
		i = 1;
		while (i < parser->mapMaxLine - 1)
		{
			if (parser->WorldMap[j][i] == '*')
			{
				if (!((parser->WorldMap[j + 1][i] == '*' || parser->WorldMap[j + 1][i] == '1') &&
				(parser->WorldMap[j - 1][i] == '*' || parser->WorldMap[j - 1][i] == '1') &&
				(parser->WorldMap[j][i + 1] == '*' || parser->WorldMap[j][i + 1] == '1') &&
				(parser->WorldMap[j][i - 1] == '*' || parser->WorldMap[j][i - 1] == '1')))
				{
					printf("There are zeros in the walls\n");
					cub_close();
				}
			}
			++i;
		}
		++j;
	}
	return (0);
}

int ft_parser(t_parser *parser, char *path)
{
	int sizex, sizey;
	mlx_get_screen_size(vars.mlx, &sizex, &sizey);
	int mapFD = open(path, 0666);
	if (mapFD < 3)
	{
		printf("Map path error!!!\n");
		cub_close();
	}
	int gnl = 1;
	char *line;
	while (gnl > 0)
	{
		int i = 0;
		gnl = get_next_line(mapFD, &line);
		while (line[i] && is_space(line[i]))
			++i;
		if (line[i] == 'R')
		{
			++i;
			while (line[i] && is_space(line[i]))
				++i;
			while (line[i] && is_num(line[i]))
			{
				parser->screenWidth = parser->screenWidth * 10 + (line[i] - '0');
				++i;
			}
			if (parser->screenWidth > sizex)
				parser->screenWidth = sizex;
			while (line[i] && is_space(line[i]))
				++i;
			while (line[i] && is_num(line[i]))
			{
				parser->screenHeight = parser->screenHeight * 10 + (line[i] - '0');
				++i;
			}
			if (parser->screenHeight > sizey)
				parser->screenHeight = sizey;
			if (line[i] != '\0')
			{
				printf("There are some shit after resolution!!!");
				cub_close();
			}
			++parser->Rcheck;
		}
		if (line[i] == 'N' && line[i + 1] == 'O')
		{
			parser->texNpath = path_checker(line, i);
			++parser->NOcheck;
		}
		if (line[i] == 'S' && line[i + 1] == 'O')
		{
			parser->texSpath = path_checker(line, i);
			++parser->SOcheck;
		}
		if (line[i] == 'W' && line[i + 1] == 'E')
		{
			parser->texWpath = path_checker(line, i);
			++parser->WEcheck;
		}
		if (line[i] == 'E' && line[i + 1] == 'A')
		{
			parser->texEpath = path_checker(line, i);
			++parser->EAcheck;
		}
		if (line[i] == 'S' && is_space(line[i + 1]) == 1)
		{
			parser->spritePath = path_checker(line, i);
			++parser->Scheck;
		}
		if (line[i] == 'F')
		{
			parser->bottomColor =  ft_colors(line, i);
			++parser->Fcheck;
		}
		if (line[i] == 'C')
		{
			parser->topColor =  ft_colors(line, i);
			++parser->Ccheck;
		}
		if (line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != 'R' && line[i] != 'F' && line[i] != 'C' && line[i])
		{
			printf("Shit detected - %c\n", line[i]);
			cub_close();
		}
		if (line[i] == '1')
		{
			if (filechecker(parser))
			{
				if (parser->mapMaxLine < ft_strlen(line))
					parser->mapMaxLine = ft_strlen(line);
				++parser->mapLineCount;
			}
		}
	}
	close(mapFD);
	map_init(parser->mapMaxLine, parser->mapLineCount, parser);
	mapFD = open(path, 0666);
	gnl = 1;
	int number = -1;
	while (gnl > 0)
	{
		int i = 0;
		gnl = get_next_line(mapFD, &line);
		while (is_space(line[i])) 
			++i;
		if (line[i] == '1')
		{
			++number;
			ft_mappars(line, parser, number);
		}
	}
	if (parser->NSWEcount != 1)
	{
		printf("Player position error!!!\n");
		cub_close();
	}
	close(mapFD);
	final_pars(parser);
	return (0);
}
