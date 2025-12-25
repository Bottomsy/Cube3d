/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adahab <adahab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:06:19 by waissi            #+#    #+#             */
/*   Updated: 2025/12/25 15:09:29 by adahab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_format(char *map)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (map[i])
		i++;
	if (i <= 4)
		return (0);
	i -= 4;
	while (FORMAT[k] && map[i])
	{
		if (FORMAT[k] != map[i])
			return (0);
		k++;
		i++;
	}
	return (1);
}

int	check_tformat(char *map)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (map[i])
		i++;
	if (i <= 4)
		return (0);
	i -= 4;
	while (TFORMAT[k] && map[i])
	{
		if (TFORMAT[k] != map[i])
		{
			printf(RED "Error: Invalid texture format\n" RESET);
			return (-1);
		}
		k++;
		i++;
	}
	return (1);
}

int	check_map(char **map)
{
	int		i;
	int		j;
	char	**map_copy;

	if (init_map_copy(&map_copy, map, &i) == -1)
		return (-1);
	while (map_copy[i])
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == ' ')
			{
				if (flfl(map_copy, i, j))
				{
					printf(RED "Error: Invalid map\n" RESET);
					ft_free_map_map(map_copy);
					return (-1);
				}
			}
			j++;
		}
		i++;
	}
	return (ft_free_map_map(map_copy), 0);
}

int	check_up_down(char **map)
{
	int	j;
	int	len;
	int	i;
	int	fi;

	j = 0;
	len = ft_strlen(map[0]);
	while (j < len)
	{
		fi = 0;
		while (map[fi] && map[fi][j] == ' ')
			fi++;
		if (!map[fi])
		{
			j++;
			continue ;
		}
		if (check_down(map, &i, fi, j) == -1)
			return (-1);
		while (map[i] && map[i][j] != ' ')
			i++;
		if (check_up(map, i, &j) == -1)
			return (-1);
	}
	return (0);
}

int	check_left_right(char **map)
{
	int	i;
	int	len;
	int	fj;
	int	j;

	i = 0;
	while (map[i])
	{
		if (check_len(&len, map, &i, &fj))
			continue ;
		while (fj < len && map[i][fj] == ' ')
			fj++;
		if (fj >= len)
		{
			i++;
			continue ;
		}
		if (check_right(map, i, fj, &j) == -1)
			return (-1);
		while (j < len && map[i][j] != ' ')
			j++;
		if (check_left(map, &i, j) == -1)
			return (-1);
	}
	return (0);
}
