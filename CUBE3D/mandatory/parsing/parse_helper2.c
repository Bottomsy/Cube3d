#include "../cub3d.h"

float get_angle(char d)
{
	if (d == 'S')
		return 270 * PI / 180;
	else if (d == 'N')
		return 90 * PI / 180;
	else if (d == 'W')
		return 180 * PI / 180;
	else if (d == 'E')
		return 0 * PI / 180;
	return 0;
}

void get_player_info(t_player *player, char **map)
{
	int i = 0, j, pos = 0;
    while (i < player->map->rows)
    {
        j = 0;
        while (j < player->map->cols)
        {
			if (pos == 2)
			{
				ft_free(player);
				print_error(1);
			}
			if ( map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				player->angle = get_angle(map[i][j]);
				player->px = ((float)j * TILESIZE) + (TILESIZE / 2);
				player->py = ((float)i * TILESIZE) + (TILESIZE / 2);
				pos++;
			}
			j++;
}
        i++;
    }
	if (pos == 0)
	{
		ft_free(player);
		print_error(2);
	}
}

int flfl(char **map, int y, int x)
{
    if (y < 0 || x < 0)
        return 0;
    if (map[y] == NULL || map[y][x] == '\0')
	    return 0;

    if (map[y][x] == '1' || map[y][x] == 'V' )
        return 0;
    else if (map[y][x] == ' ')
   	 map[y][x] = 'V';
    else
	    return 1;

    if (flfl(map, y + 1, x)) return 1;
    if (flfl(map, y - 1, x)) return 1;
    if (flfl(map, y, x + 1)) return 1;
    if (flfl(map, y, x - 1)) return 1;

    return 0;
}

int extract_num(char *info, int *val)
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
	while(info[i] != '\n' && info[i] != ',' && info[i] != ' ')
		num[k++] = info[i++];
	num[k] = '\0';
	k = 0;
	if (num[k] < '0' || num[k] > '9')
	{
		free(num);
		*val = -1;
		if(info[i] == ',')
			i++;
		return i;
	}
	if (atoi(num) < 0 || atoi(num) > 255)
		(*val) = -1;
	else
		(*val) = atoi(num);
	free(num);
	if(info[i] == ',')
		i++;
	return i;
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