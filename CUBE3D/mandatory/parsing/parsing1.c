#include "../cub3d.h"

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

void pad_map(t_map *map, char *info, int i, int x, int y)
{
    while(info[i])
    {
        if(x < map->cols)
        {
            while(x < map->cols && (info[i] == '\n' || !info[i + 1]))
                map->map[y][x++] = ' ';
            if(info[i] != '\n' && info[i + 1])
                map->map[y][x++] = info[i++];
        }
        while(x == map->cols && info[i] == ' ')
            i++;
        if(y < map->rows && x == map->cols)
        {
            map->map[y][x] = '\0';
            x = 0;
            i++;
            y++;
        }
    }
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
    map->map = malloc((map->rows+1) * sizeof(char *));
    while(y < map->rows)
        map->map[y++] = malloc(map->cols + 1);
    map->map[y] = NULL;
    y = 0;
    pad_map(map, info, i, x, y);    
}

char **split_info(t_player *player, char *info)
{
	t_map *map;
	t_textures *txtrs;
	
	map = malloc(sizeof(t_map));
	txtrs = malloc(sizeof(t_textures));
	map->map_start = fill_textures(txtrs, info);
	fill_map(map, info);
	int x = 0;
	int y = 0;
	while(y < map->rows)
	{
		while(x < map->cols)
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

char **treat_map(t_player *player, char *map)
{
	int fd;
	char **res;
	if(!check_format(map))
	{
		printf("Error: Wrong file format\n");
		return NULL;
	}
	fd = open(map, O_RDONLY);
	res = split_info(player, read_map(fd));
	close(fd);
	return res;
}













