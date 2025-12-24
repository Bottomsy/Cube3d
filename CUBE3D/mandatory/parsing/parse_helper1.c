#include "../cub3d.h"

int coma_return(char *info, int *i, int **rgb)
{
	(*i)++;
	if (!check_fasilat(info))
	{
		**rgb = -1;
		while (info[*i] != '\n')
			(*i)++;
		return (*i);
	}
	return (-2);
}

void init_rgb(int *r, int *g, int *b, int *i)
{
	*r = -2;
	*g = -2;
	*b = -2;
	*i = 0;
}

void count_cols(char *info, int *cols, int *i)
{
	while (info[*i] == ' ')
	{
		(*cols)++;
		(*i)++;
	}
	while (info[*i] && info[*i] != '\n')
	{
		(*cols)++;
		(*i)++;
	}
	
}

void create_map(t_map *map, t_pointers **ptrs)
{
	int y;

	y = 0;
	map->map = ft_malloc(ptrs, (map->rows + 1) * sizeof(char *));
	while (y < map->rows)
	{
		map->map[y] = ft_malloc(ptrs, map->cols + 1);
		ft_memset(map->map[y], '\0', map->cols + 1);
		y++;
	}
	map->map[y] = NULL;
}
