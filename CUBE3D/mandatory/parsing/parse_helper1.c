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
	if (!strcmp(path, "Error"))
	{
		printf(RED"Error: No space between identifier and path\n"RESET);
		return -1;
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

	i = 1;
	k = 0;
	if (info[i + 1] != ' ')
	{
		*path = malloc(6);
		ft_strcpy(*path, "Error");
		while (info[i] != '\n')
			i++;
		i++;
		return (i);
	}
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
int check_fasilat(char *info)
{
	int i = 0;
	int fasila = 0;
	while (info[i] != '\n')
	{
		if (info[i] == ',')
			fasila++;
		i++;
	}
	if (fasila != 2)
		return 0;
	return i;
}

int check_rgb_values(char *info, int *r, int *g, int *b)
{
	if (info[0] != '\n')
		return -1;
	if (*r == -1 || *g == -1 || *b == -1)
		return -1;
	else if (*r == -2 || *g == -2 || *b == -2)
		return -2;
	else
		return ((*r << 16) | (*g << 8) | *b);
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
	if (!check_fasilat(info))
	{
		*rgb = -1;
		while (info[i] != '\n')
			i++;
		return (i);
	}
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
	free(arr);
	return (biggest);
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

int	get_cols(char *info)
{
	int	i;
	int	j;
	int	col;
	int	*cols;
	int rows;

	j = 0;
	i = 0;
	rows = get_rows(info);
	if (rows == -1)
		return (-1);
	cols = malloc(rows * sizeof(int));
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
void check_only_spaces(char *info, int i, int *only_spaces)
{
	*only_spaces = 1;
	while (i >= 0 && info[i] != '\n')
	{
		if (info[i] != ' ')
		{
			*only_spaces = 0;
			break;
		}
		i--;
	}
}
int	get_rows(char *info)
{
	int i;
	int rows;
	int j;
	int only_spaces;

	rows = 0;
	i = 0;
	while (info[i])
	{
		if ((info[i] == '\n') && i > 0 && (info[i - 1] != '\n'))
		{
			j = i - 1;
			check_only_spaces(info, j, &only_spaces);
			if (only_spaces)
				return (printf(RED"Error: Empty line in map\n"RESET), -1);
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
