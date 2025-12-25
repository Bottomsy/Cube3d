/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adahab <adahab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:01:55 by waissi            #+#    #+#             */
/*   Updated: 2025/12/25 15:10:34 by adahab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_rgb_values(char *info, int *r, int *g, int *b)
{
	if (info[0] != '\n')
		return (-1);
	if (*r == -1 || *g == -1 || *b == -1)
		return (-1);
	else if (*r == -2 || *g == -2 || *b == -2)
		return (-2);
	else
		return ((*r << 16) | (*g << 8) | *b);
}

void	check_only_spaces(char *info, int i, int *only_spaces)
{
	*only_spaces = 1;
	while (i >= 0 && info[i] != '\n')
	{
		if (info[i] != ' ')
		{
			*only_spaces = 0;
			break ;
		}
		i--;
	}
}

int	check_players(char **map)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	j = 0;
	pos = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (pos == 2)
				return (print_error(1));
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'E')
				pos++;
			j++;
		}
		i++;
	}
	if (pos < 1)
		return (print_error(2));
	return (0);
}
