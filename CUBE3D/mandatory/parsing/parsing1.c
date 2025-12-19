#include "../cub3d.h"

int	fill_textures(t_textures *txtrs, char *info)
{
	int	i;
	int	elements;
	int	m;

	i = 0;
	elements = 0;
	m = 0;
	while (info[i] && !m)
	{
		if (info[i] == 'N' && info[i + 1] == 'O')
			i += get_path(info + i, &txtrs->no, &elements);
		else if (info[i] == 'S' && info[i + 1] == 'O')
			i += get_path(info + i, &txtrs->so, &elements);
		else if (info[i] == 'W' && info[i + 1] == 'E')
			i += get_path(info + i, &txtrs->we, &elements);
		else if (info[i] == 'E' && info[i + 1] == 'A')
			i += get_path(info + i, &txtrs->ea, &elements);
		else if (info[i] == 'C')
			i += get_rgb(info + i, &txtrs->c, &elements);
		else if (info[i] == 'F')
			i += get_rgb(info + i, &txtrs->f, &elements);
		else if (info[i] == '1' || info[i] == '0')
		{
			if (elements == 6)
			{
				while (i > 0 && info[i - 1] != '\n')
					i--;
				if (info[i - 2] != '\n')
				{
					printf(RED "Error: Extra information before map\n" RESET);
					return (-1);
				}
				m = 1;
			}
			else
			{
				return (-1);
			}
		}
		else
			i++;
	}
	if (elements == 6 && m)
		return (i);
	return (i);
}

void	pad_map(t_map *map, char *info, int *i)
{
	int y;
	int x;

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

int	fill_map(t_map *map, char *info)
{
	int	i;
	int	y;
	int	j;

	y = 0;
	i = map->map_start;
	printf("map start index: %d\n", i);
	while (info[i] && info[i] == '\n')
		i++;
	if (info[i] == '\0')
	{
		printf(RED "Error: Map is empty\n" RESET);
		return (0);
	}
	map->rows = get_rows(info + i);
	if (map->rows == -1)
		return (0);
	printf("rows: %d\n", map->rows);
	map->cols = get_cols(info + i);
	if (map->cols == -1)
		return (0);
	printf("cols: %d\n", map->cols);
	map->map = malloc((map->rows + 1) * sizeof(char *));
	while (y < map->rows)
	{
		map->map[y] = malloc(map->cols + 1);
		j = 0;
		while (j <= map->cols)
			map->map[y][j++] = '\0';
		y++;
	}
	map->map[y] = NULL;
	pad_map(map, info, &i);
	while (info[i] && (info[i] == '\n' || info[i] == ' '))
		i++;
	if (info[i] != '\0')
	{
		printf(RED "Error: Extra information after map\n" RESET);
		return (0);
	}
	return (1);
}

char	**split_info(t_player *player, char *info)
{
	t_map		*map;
	t_textures	*txtrs;
	int			x;
	int			y;

	map = malloc(sizeof(t_map));
	txtrs = malloc(sizeof(t_textures));
	init_texts(txtrs);
	map->map_start = fill_textures(txtrs, info);
	map->map = NULL;
	if (check_textures(txtrs, map, info) == -1)
		return (NULL);
	if (!fill_map(map, info))
	{
		return (ft_free_parse(map, txtrs, info));
	}
	x = 0;
	y = 0;
	while (y < map->rows)
	{
		while (x < map->cols)
			printf("%c", map->map[y][x++]);
		printf("\n");
		y++;
		x = 0;
	}
	printf("%s\n", txtrs->so);
	printf("%s\n", txtrs->ea);
	player->map = map;
	player->textures = txtrs;
	free(info);
	return (map->map);
}

char	**treat_map(t_player *player, char *map)
{
	int		fd;
	char	**res;

	if (!check_format(map))
	{
		printf("Error: Wrong file format\n");
		return (NULL);
	}
	fd = open(map, O_RDONLY);
	res = split_info(player, read_map(fd));
	close(fd);
	return (res);
}
