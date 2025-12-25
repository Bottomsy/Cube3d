#include "../cub3d.h"

int	coma_return(char *info, int *i, int **rgb)
{
	(*i)++;
	if (!check_commas_num(info))
	{
		**rgb = -1;
		while (info[*i] != '\n')
			(*i)++;
		return (*i);
	}
	return (-2);
}

void	count_cols(char *info, int *cols, int *i)
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

void	create_map(t_map *map, t_pointers **ptrs)
{
	int	y;

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

void	fill_player(t_player *player, t_data img[5], t_ray **ray
		, t_pointers **ptrs)
{
	player->ray = *ray;
	get_player_info(player, player->map->map);
	player->img = img;
	player->dir = 0;
	player->dor = 0;
	player->sdir = 0;
	player->ray_num = (WIDTH / STRIPESIZE);
	player->ptrs = *ptrs;
}
