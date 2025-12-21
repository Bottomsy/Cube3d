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

char	**copy_map(char **mapp)
{
	char	**map;
	int		y;
	int		r;

	y = 0;
	r = 0;
	while (mapp[r])
		r++;
	map = malloc((r + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	y = 0;
	while (y < r)
	{
		map[y] = ft_strdup(mapp[y]);
		y++;
	}
	map[y] = NULL;
	return (map);
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
	*val = ft_atoi(num);
	free(num);
	if (info[i] == ',')
		i++;
	return (i);
}

void	*check_read(char *info)
{
	printf(RED "Error: Map empty or corrupted\n" RESET);
	free(info);
	return (NULL);
}

void	*ft_malloc(size_t size, t_textures *txtrs, t_map *map, t_player *player, char *info)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf(RED "Error: Memory allocation failed\n" RESET);
		if (player)
			ft_free(player);
		if (map)
			ft_free_map(map);
		if (txtrs)
			ft_free_textures(txtrs);
		if (info)
			free(info);
		exit(EXIT_FAILURE);
	}
	return (ptr);
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
	while (1)
	{
		b = read(fd, tmp, READSIZE);
		if (b <= 0)
			break ;
		new = ft_malloc(b + bread + 1, NULL, NULL, NULL, final);
		if (bread)
			ft_memcpy(new, final, bread);
		ft_memcpy(new + bread, tmp, b);
		new[b + bread] = '\0';
		bread += b;
		free(final);
		final = new;
	}
	if (final == NULL || final[0] == '\0' || b < 0)
		return (check_read(final));
	return (final);
}
