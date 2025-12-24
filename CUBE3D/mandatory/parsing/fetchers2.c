#include "../cub3d.h"

void	get_player_info(t_player *player, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < player->map->rows)
	{
		j = 0;
		while (j < player->map->cols)
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				player->angle = get_angle(map[i][j]);
				player->px = ((float)j * TILESIZE) + (TILESIZE / 2);
				player->py = ((float)i * TILESIZE) + (TILESIZE / 2);
			}
			j++;
		}
		i++;
	}
}

int	get_path(char *info, char **path, int *elements, t_pointers **ptrs)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	if (info[i + 1] != ' ')
	{
		*path = ft_malloc(ptrs, 6);
		ft_strcpy(*path, "Error");
		while (info[i] != '\n')
			i++;
		i++;
		return (i);
	}
	if ((*path) != NULL)
	{
		(*path) = NULL;
		
		while (info[i] != ' ')
			i++;
		i++;
		while (info[i] != '\n')
			i++;
		return (i);
	}
	i++;
	while (info[i + k] != '\n')
		k++;
	(*path) = ft_malloc(ptrs, k + 1);
	k = 0;
	while (info[i] == ' ')
		i++;
	while (info[i] != '\n')
		(*path)[k++] = info[i++];
	(*path)[k] = '\0';
	(*elements)++;
	return (i);
}

int fetch_recources(t_textures *txtrs, char *info, int *elements, t_pointers **ptrs)
{
	int i;

	i = 0;
	if (info[i] == 'N' && info[i + 1] == 'O')
		i += get_path(info + i, &txtrs->no, elements, ptrs);
	else if (info[i] == 'S' && info[i + 1] == 'O')
		i += get_path(info + i, &txtrs->so, elements, ptrs);
	else if (info[i] == 'W' && info[i + 1] == 'E')
		i += get_path(info + i, &txtrs->we, elements, ptrs);
	else if (info[i] == 'E' && info[i + 1] == 'A')
		i += get_path(info + i, &txtrs->ea, elements, ptrs);
	else if (info[i] == 'C')
		i += get_rgb(info + i, &txtrs->c, elements, ptrs);
	else if (info[i] == 'F')
		i += get_rgb(info + i, &txtrs->f, elements, ptrs);
	return (i);
}

int	extract_num(char *info, int *val, t_pointers **ptrs)
{
	char	*num;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (info[i + k] != '\n' && info[i + k] != ',')
		k++;
	num = ft_malloc(ptrs, k + 1);
	k = 0;
	while (info[i] != '\n' && info[i] != ',')
		num[k++] = info[i++];
	num[k] = '\0';
	k = 0;
	*val = ft_atoi(num);
	if (info[i] == ',')
		i++;
	return (i);
}
