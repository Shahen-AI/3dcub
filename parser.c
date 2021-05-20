#include "cub3d.h"

int is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int parser()
{
	int mapFD = open("maps/3dmap.cub", 0666);
	int gnl = 1;
	char *line;
	while (gnl == 1)
	{
		int i = 0;
		gnl = get_next_line(mapFD, &line);
		while (line[i] && is_space(line[i]))
			++i;
		if (line[i] == 'R')
		{
			++i;
			global.screenHeight = 0;
			global.screenWidth = 0;
			while (line[i] && is_space(line[i]))
				++i;
			while (line[i] && is_num(line[i]))
			{
				global.screenWidth = global.screenWidth * 10 + (line[i] - '0');
				++i;
			}
			while (line[i] && is_space(line[i]))
				++i;
			while (line[i] && is_num(line[i]))
			{
				global.screenHeight = global.screenHeight * 10 + (line[i] - '0');
				++i;
			}
			// global.screenWidth = 1920;
			// global.screenHeight = 1080;
			printf("R - w %d & h %d\n", global.screenWidth, global.screenHeight);
		}
		if (line[i] == 'N' && line[i + 1] == 'O')
		{
			printf("NO\n");
		}
		if (line[i] == 'S' && line[i + 1] == 'O')
		{
			printf("SO\n");
		}
		if (line[i] == 'W' && line[i + 1] == 'E')
		{
			printf("WE\n");
		}
		if (line[i] == 'E' && line[i + 1] == 'A')
		{
			printf("EA\n");
		}
		if (line[i] == 'S' && is_space(line[i + 1]) == 1)
		{
			printf("S\n");
		}
		if (line[i] == 'F')
		{
			printf("F\n");
		}
		if (line[i] == 'C')
		{
			printf("C\n");
		}
	}
	// printf("testing - %s\n", line);
	return (0);
}
