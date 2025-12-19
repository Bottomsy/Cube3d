#include "../cub3d.h"

int	check_textures(t_textures *texts, t_map *map, char *line)
{
	if ((check_valid_path(texts->no) == -1 || check_valid_path(texts->so) == -1
			|| check_valid_path(texts->ea) == -1
			|| check_valid_path(texts->we) == -1)
		|| (check_tformat(texts->no) == -1 || check_tformat(texts->so) == -1
			|| check_tformat(texts->ea) == -1 || check_tformat(texts->we) == -1)
		|| (check_rgb(texts->c) == -1 || check_rgb(texts->f) == -1)
		|| map->map_start == -1)
	{
		ft_free_parse(map, texts, line);
		return (-1);
	}
	return (0);
}

int	check_valid_path(char *path)
{
	int	fd;

	if (!path)
	{
		printf(RED "Error: Missing or duplicate texture path\n" RESET);
		return (-1);
	}
	fd = open(path, O_RDWR);
	if (fd == -1)
	{
		printf(RED "Error: Invalid Texture File\n" RESET);
		return (-1);
	}
	close(fd);
	return (1);
}

int	get_path(char *info, char **path, int *elements)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if ((*path) != NULL)
	{
		free(*path);
		(*path) = NULL;
		while (info[i] != ' ')
			i++;
		i++;
		while (info[i] != '\n')
			i++;
		return (i);
	}
	while (info[i] != ' ')
		i++;
	i++;
	while (info[i + k] != '\n')
		k++;
	(*path) = malloc(k + 1);
	k = 0;
	while (info[i] == ' ')
		i++;
	while (info[i] != '\n')
		(*path)[k++] = info[i++];
	(*path)[k] = '\0';
	(*elements)++;
	return (i);
}

int	get_rgb(char *info, int *rgb, int *elements)
{
	int	i;
	int	r;
	int	g;
	int	b;

	r = -2;
	g = -2;
	b = -2;
	i = 0;
	while (info[i] != ' ')
		i++;
	i++;
	if ((*rgb) != -2)
	{
		*rgb = -2;
		while (info[i] != '\n')
			i++;
		return (i);
	}
	while (info[i] == ' ')
		i++;
	i += extract_num(info + i, &r);
	i += extract_num(info + i, &g);
	i += extract_num(info + i, &b);
	if (info[i] != '\n')
	{
		*rgb = -1;
		return (i);
	}
	if (r == -1 || g == -1 || b == -1)
	{
		*rgb = -1;
		return (i);
	}
	else if (r == -2 || g == -2 || b == -2)
	{
		*rgb = -2;
		return (i);
	}
	else
		(*rgb) = (r << 16) | (g << 8) | b;
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
	free(arr);
	return (biggest);
}

int	get_cols(char *info)
{
	int	i;
	int	j;
	int	col;
	int	*cols;
	int rows; // norminette invalid

	j = 0;
	i = 0;
	rows = get_rows(info);
	if (rows == -1)
		return (-1);
	cols = malloc(rows * sizeof(int));
	while (j < rows)
	{
		col = 0;
		while (info[i] == ' ')
		{
			col++;
			i++;
		}
		while (info[i] && info[i] != '\n' && info[i] != ' ')
		{
			col++;
			i++;
		}
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
	int i;
	int rows;

	rows = 0;
	i = 0;
	while (info[i])
	{
		if ((info[i] == '\n') && i > 0 && (info[i - 1] != '\n'))
		{
			int j = i - 1;
			int only_spaces = 1;
			while (j >= 0 && info[j] != '\n')
			{
				if (info[j] != ' ')
				{
					only_spaces = 0;
					break;
				}
				j--;
			}
			if (only_spaces)
			{
				printf(RED"Error: Empty line in map\n"RESET);
				return (-1);
			}
			if (!only_spaces)
				rows++;
		}
		else if (info[i] == '\n' && i > 0 && (info[i - 1] == '\n'))
			break;
		i++;
	}
	if (info[i] == '\0' && i > 0 && info[i - 1] != '\n')
		rows++;
	return (rows);
}
