#include "../includes/cube.h"

int check_format(char *map)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while(map[i])
		i++;
	//error for having no format
	if(i <= 4)
		return (0);
	i -= 4;
	while(FORMAT[k] && map[i])
	{
		//error for not having the wrong format
		if(FORMAT[k] != map[i])
			return (0);
		k++;
		i++;
	}
	return (1);
}

char *read_map(int fd)
{
	char *new;
	char tmp[READSIZE + 1];
	char *final;
	ssize_t b;
	ssize_t bread;

	final = NULL;
	bread = 0;
	b = 0;
	while((b = read(fd, tmp, READSIZE)) > 0)
	{
		tmp[b] = '\0';
		//gay ass malloc failure handling
		new = malloc(b + bread + 1);
		if(bread)
			memcpy(new, final, bread);
		memcpy(new + bread, tmp, b);
		new[b + bread] = '\0';
		bread += b;
		free(final);
		final = new;
	}
	return final;
}

int get_path(char *info, char **path, int *elements)
{
	int i;
	int k;
	
	i = 0;
	k = 0;
	while(info[i] != ' ')
		i++;
	i++;
	while(info[i + k] != '\n')
		k++;
	(*path) = malloc(k);
	k = 0;
	while(info[i] != '\n')
		(*path)[k++] = info[i++];
	(*path)[k] = '\0';
	(*elements)++;
	return i;
}

int extract_num(char *info, unsigned char *val)
{
	char *num;
	int i;
	int k;

	i = 0;
	k = 0;
	while(info[i + k] != '\n' && info[i + k] != ',')
		k++;
	num = malloc(k + 1);
	k = 0;
	while(info[i] != '\n' && info[i] != ',')
		num[k++] = info[i++];
	num[k] = '\0';
	(*val) = (unsigned char)atoi(num);
	free(num);
	if(info[i] == ',')
		i++;
	return i;
}

int get_rgb(char *info, unsigned int *rgb, int *elements)
{
	int i;
	unsigned char r;
	unsigned char g;
	unsigned char b;

	i = 0;
	while(info[i] != ' ')
		i++;
	i++;
	i += extract_num(info + i, &r);
	i += extract_num(info + i, &g);
	i += extract_num(info + i, &b);
	(*rgb) = (r << 16) | (g << 8) | b;
	(*elements)++;
	return i;
}

int fill_textures(t_textures *txtrs, char *info)
{
	int i;
	int elements;
	
	i = 0;
	elements = 0;
	while(info[i])
	{
		if(info[i] == 'N')
			i += get_path(info + i, &txtrs->no, &elements);
		else if(info[i] == 'S')
			i += get_path(info + i, &txtrs->so, &elements);
		else if(info[i] == 'W')
			i += get_path(info + i, &txtrs->we, &elements);
		else if(info[i] == 'E')
			i += get_path(info + i, &txtrs->ea, &elements);
		else if(info[i] == 'C')
			i += get_rgb(info + i, &txtrs->c, &elements);
		else if(info[i] == 'F')
			i += get_rgb(info + i, &txtrs->f, &elements);
		if(elements == 6)
			return (i);
		i++;
	}
	return (0);
}

int get_cols(char *info)
{
	int i;

	i = 0;
	while(info[i] != '\n')
		i++;
	return i;
}

int get_rows(char *info)
{
	int i;
	int rows;

	rows = 0;
	i = 0;
	while(info[i])
	{
		if(info[i] == '\n')
			rows++;
		i++;
	}
	return (rows);
}

void fill_map(t_map *map, char *info)
{
	int i;
	int x;
	int y;
	
	x = 0;
	y = 0;
	i = map->map_start;
	while(info[i] && info[i] == '\n')
		i++;
	map->rows = get_rows(info + i);
	map->cols = get_cols(info + i);
	map->map = malloc(map->cols * sizeof(char *));
	while(y < map->cols)
		map->map[y++] = malloc(map->rows + 1);
	y = 0;
	while(info[i])
	{
		if(info[i] != '\n')
			map->map[y][x++] = info[i++];
		else
		{
			map->map[y][++x] = '\0';
			x = 0;
			i++;
			y++;
		}
	}
}

void split_info(char *info)
{
	t_map *map;
	t_textures *txtrs;
	
	map = malloc(sizeof(t_map));
	txtrs = malloc(sizeof(t_textures));
	map->map_start = fill_textures(txtrs, info);
	fill_map(map, info);
	/*int x = 0;
	int y = 0;
	while(y < map->rows)
	{
		while(x < map->cols)
			printf("%c", map->map[y][x++]);
		printf("\n");
		y++;
		x = 0;
	}*/
	printf("%s\n", txtrs->so);
	printf("%s\n", txtrs->ea);
}

int treat_map(char *map)
{
	int fd;

	if(!check_format(map))
		return (0);
	fd = open(map, O_RDONLY);
	split_info(read_map(fd));
	return (1);
}
