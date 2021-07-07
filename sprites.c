#include "cub3d.h"

void fill_sprites(t_parser *parser)
{
    int count = 0;

    for (int y = 0; y < parser->mapLineCount; ++y)
    {
        for (int x = 0; x < parser->mapMaxLine; ++x)
        {
            if (parser->WorldMap[y][x] == '2')
            {
                parser->sprites.sprites[count]->x = (double)y + 0.5;
                parser->sprites.sprites[count]->y = (double)x + 0.5;
                parser->sprites.sprites[count]->distance = 0;
                count++;
            }
        }
    }
}

void init_sprites(t_parser *parser)
{
    parser->sprites.sprites = malloc(parser->sprites.count * (sizeof(t_spr_atr*)));
    for (int i = 0; i < parser->sprites.count; ++i)
        parser->sprites.sprites[i] = malloc(sizeof(t_spr_atr));
    fill_sprites(parser);
}

void bubble_sort(t_parser *parser)
{
    int i;
	int j;
    float tmp;

	i = 1;
	while (i < parser->sprites.count)
	{
		j = i;
		while (j > 0 && (int)parser->sprites.sprites[j]->distance > (int)parser->sprites.sprites[j - 1]->distance)
		{
            tmp = parser->sprites.sprites[j - 1]->distance;
            parser->sprites.sprites[j - 1]->distance = parser->sprites.sprites[j]->distance;
            parser->sprites.sprites[j]->distance = tmp;
            tmp = parser->sprites.sprites[j - 1]->x;
            parser->sprites.sprites[j - 1]->x = parser->sprites.sprites[j]->x;
            parser->sprites.sprites[j]->x = tmp;
            tmp = parser->sprites.sprites[j - 1]->y;
            parser->sprites.sprites[j - 1]->y = parser->sprites.sprites[j]->y;
            parser->sprites.sprites[j]->y = tmp;
			--j;
		}
		++i;
	}
}

void			sort_sprites(t_parser *parser)
{
	int i;

	i = -1;
	while (++i < parser->sprites.count)
	{
		parser->sprites.sprites[i]->distance = ((positions.posX - parser->sprites.sprites[i]->x)
		* (positions.posX - parser->sprites.sprites[i]->x)
		+ (positions.posY - parser->sprites.sprites[i]->y) * (positions.posY - parser->sprites.sprites[i]->y));
	}
	if (parser->sprites.count > 1)
		bubble_sort(parser);
}