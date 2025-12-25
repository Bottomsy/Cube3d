/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waissi <waissi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:02:36 by waissi            #+#    #+#             */
/*   Updated: 2025/12/25 18:36:03 by waissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	fill_textures(t_textures *txtrs, char *info, t_pointers **ptrs)
{
	int	i;
	int	m;

	i = 0;
	m = 0;
	while (info[i] && !m)
	{
		i += fetch_recources(txtrs, info + i, &txtrs->elements, ptrs);
		if (info[i] == '1' || info[i] == '0')
		{
			if (txtrs->elements == 6)
			{
				while (i > 0 && info[i - 1] != '\n')
					i--;
				if (info[i - 2] != '\n')
					return (printf(RED "Error: Multiple maps detected\n" RESET),
						-1);
				m = 1;
			}
			else
				return (-1);
		}
		i++;
	}
	return (i);
}

void	pad_map(t_map *map, char *info, int *i)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (info[*i] && y < map->rows)
	{
		if (x < map->cols)
		{
			while (x < map->cols && (info[*i] == '\n' || info[*i] == '\0'))
				map->map[y][x++] = ' ';
			if (info[*i] != '\n' && info[*i] != '\0')
				map->map[y][x++] = info[(*i)++];
		}
		while (x == map->cols && info[*i] == ' ')
			(*i)++;
		if (y < map->rows && x == map->cols)
		{
			map->map[y][x] = '\0';
			x = 0;
			(*i)++;
			y++;
		}
	}
}

int	fill_map(t_map *map, char *info, t_pointers **ptrs)
{
	int	i;

	i = map->map_start;
	while (info[i] && info[i] == '\n')
		i++;
	if (info[i] == '\0')
		return (printf(RED "Error: Map is empty\n" RESET), 0);
	map->rows = get_rows(info + i);
	if (map->rows == -1)
		return (0);
	map->cols = get_cols(info + i, ptrs);
	create_map(map, ptrs);
	pad_map(map, info, &i);
	while (info[i] && (info[i] == '\n' || info[i] == ' '))
		i++;
	if (info[i] != '\0')
		return (printf(RED "Error: Multiple maps detected\n" RESET), 0);
	return (1);
}

char	**split_info(t_player *player, char *info, t_pointers **ptrs)
{
	t_map		*map;
	t_textures	*txtrs;

	if (!info)
		return (NULL);
	map = ft_malloc(ptrs, sizeof(t_map));
	txtrs = ft_malloc(ptrs, sizeof(t_textures));
	init_texts(txtrs);
	map->map_start = fill_textures(txtrs, info, ptrs);
	map->map = NULL;
	if (check_textures(txtrs, map) == -1)
		return (NULL);
	if (!fill_map(map, info, ptrs))
		return (NULL);
	if (check_map(map->map) == -1 || check_players(map->map) == -1)
		return (NULL);
	player->map = map;
	player->textures = txtrs;
	return (map->map);
}

char	**treat_map(t_player *player, char *map, t_pointers **ptrs)
{
	int		fd;
	char	**res;

	if (!check_format(map))
	{
		printf(RED "Error: Wrong file format\n" RESET);
		return (NULL);
	}
	fd = open(map, O_RDONLY);
	res = split_info(player, read_map(fd, ptrs), ptrs);
	close(fd);
	return (res);
}
