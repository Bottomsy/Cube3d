#include "../cub3d.h"

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

char	*read_map(int fd, t_pointers **ptrs)
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
		new = ft_malloc(ptrs, b + bread + 1);
		if (bread)
			ft_memcpy(new, final, bread);
		ft_memcpy(new + bread, tmp, b);
		new[b + bread] = '\0';
		bread += b;
		final = new;
	}
	if (final == NULL || final[0] == '\0' || b < 0)
		return (printf(RED "Error: Map empty or corrupted\n" RESET), NULL);
	return (final);
}
