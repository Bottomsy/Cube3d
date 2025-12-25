/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetchers_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waissi <waissi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:02:02 by waissi            #+#    #+#             */
/*   Updated: 2025/12/25 18:36:03 by waissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	get_rgb(char *info, int *rgb, int *elements, t_pointers **ptrs)
{
	int	i;
	int	r;
	int	g;
	int	b;

	init_rgb(&r, &g, &b, &i);
	while (info[i] != ' ')
		i++;
	if (coma_return(info, &i, &rgb) != -2)
		return (i);
	if ((*rgb) != -2)
	{
		*rgb = -2;
		while (info[i] != '\n')
			i++;
		return (i);
	}
	while (info[i] == ' ')
		i++;
	i += extract_num(info + i, &r, ptrs);
	i += extract_num(info + i, &g, ptrs);
	i += extract_num(info + i, &b, ptrs);
	*rgb = check_rgb_values(info + i, &r, &g, &b);
	(*elements)++;
	return (i);
}

int	get_biggest(int *arr, int size)
{
	int	i;
	int	biggest;

	i = 1;
	biggest = arr[0];
	while (i < size)
	{
		if (biggest < arr[i])
			biggest = arr[i];
		i++;
	}
	return (biggest);
}

int	get_cols(char *info, t_pointers **ptrs)
{
	int	i;
	int	j;
	int	col;
	int	*cols;
	int	rows;

	j = 0;
	i = 0;
	rows = get_rows(info);
	if (rows == -1)
		return (-1);
	cols = ft_malloc(ptrs, rows * sizeof(int));
	while (j < rows)
	{
		col = 0;
		count_cols(info, &col, &i);
		if (info[i] && info[i] == '\n')
			i++;
		while (info[i] && info[i] == ' ')
			i++;
		if (info[i] && info[i] == '\n')
			i++;
		cols[j++] = col;
	}
	return (get_biggest(cols, rows));
}

int	get_rows(char *info)
{
	int	i;
	int	rows;
	int	j;
	int	only_spaces;

	rows = 0;
	i = 0;
	while (info[i])
	{
		if ((info[i] == '\n') && i > 0 && (info[i - 1] != '\n'))
		{
			j = i - 1;
			check_only_spaces(info, j, &only_spaces);
			if (only_spaces)
				return (printf(RED "Error: Empty line in map\n" RESET), -1);
			if (!only_spaces)
				rows++;
		}
		else if (info[i] == '\n' && i > 0 && (info[i - 1] == '\n'))
			break ;
		i++;
	}
	if (info[i] == '\0' && i > 0 && info[i - 1] != '\n')
		rows++;
	return (rows);
}

float	get_angle(char d)
{
	if (d == 'S')
		return (270 * PI / 180);
	else if (d == 'N')
		return (90 * PI / 180);
	else if (d == 'W')
		return (180 * PI / 180);
	else if (d == 'E')
		return (0 * PI / 180);
	return (0);
}
