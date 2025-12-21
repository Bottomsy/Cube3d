#include "../cub3d.h"

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

int check_players(t_player *player,char **map)
{
	int i;
	int j;
	int pos;

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
	return 0;
}

void	get_player_info(t_player *player, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < player->map->rows)
	{
		j = 0;
		while (j < player->map->cols)
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				player->angle = get_angle(map[i][j]);
				player->px = ((float)j * TILESIZE) + (TILESIZE / 2);
				player->py = ((float)i * TILESIZE) + (TILESIZE / 2);
			}
			j++;
		}
		i++;
	}
}

char **copy_map(char **mapp)
{
    char **map;
    int y = 0;
    int x = 0;
    int r = 0;
    int c = 0;

    while(mapp[y++])
        r++;
    y = 0;
    c = 134;
    map = malloc(r * sizeof(char *));
    while(y < r)
        map[y++] = malloc(c * sizeof(char));
    y = 0;
    while(y < r)
    {
        x = 0;
        while(x < c)
        {
            map[y][x] = mapp[y][x];
            x++;
        }
        map[y][x] = '\0';
        y++;
    }
    map[y] = NULL;
    return map;
}

int	flfl(char **map, int y, int x)
{
	if (y < 0 || x < 0)
		return (0);
	if (map[y] == NULL || map[y][x] == '\0')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	else if (map[y][x] == ' ')
		map[y][x] = 'V';
	else
		return (1);
	if (flfl(map, y + 1, x))
		return (1);
	if (flfl(map, y - 1, x))
		return (1);
	if (flfl(map, y, x + 1))
		return (1);
	if (flfl(map, y, x - 1))
		return (1);
	return (0);
}

int	extract_num(char *info, int *val)
{
	char	*num;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (info[i + k] != '\n' && info[i + k] != ',')
		k++;
	num = malloc(k + 1);
	k = 0;
	while (info[i] != '\n' && info[i] != ',')
		num[k++] = info[i++];
	num[k] = '\0';
	k = 0;
	if (num[k] < '0' || num[k] > '9') // to handle non digit chars with ft_atoi
	{
		free(num);
		*val = -1;
		if (info[i] == ',')
			i++;
		return (i);
	}
	if (atoi(num) < 0 || atoi(num) > 255)
		(*val) = -1;
	else
		(*val) = atoi(num);
	free(num);
	if (info[i] == ',')
		i++;
	return (i);
}

char	*read_map(int fd)
{
	char	*new;
	char	tmp[READSIZE + 1];
	char	*final;
	ssize_t	b;
	ssize_t	bread;

	final = NULL;
	bread = 0;
	b = 0;
	while ((b = read(fd, tmp, READSIZE)) > 0) // norminette invalid
	{
		tmp[b] = '\0';
		// gay ass malloc failure handling
		new = malloc(b + bread + 1);
		if (bread)
			memcpy(new, final, bread);
		memcpy(new + bread, tmp, b);
		new[b + bread] = '\0';
		bread += b;
		free(final);
		final = new;
	}
	return (final);
}
