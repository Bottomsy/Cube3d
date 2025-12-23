#include "../cub3d.h"

int	check_format(char *map)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (map[i])
		i++;
	if (i <= 4)
		return (0);
	i -= 4;
	while (FORMAT[k] && map[i])
	{
		if (FORMAT[k] != map[i])
			return (0);
		k++;
		i++;
	}
	return (1);
}

int	check_tformat(char *map)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (map[i])
		i++;
	if (i <= 4)
		return (0);
	i -= 4;
	while (TFORMAT[k] && map[i])
	{
		if (TFORMAT[k] != map[i])
		{
			printf(RED "Error: Invalid texture format\n" RESET);
			return (-1);
		}
		k++;
		i++;
	}
	return (1);
}
int tile_not_one(char **map, int i, int fj, int *j)
{
	if (map[i][fj] != '1')
	{
		printf(RED "Error: Invalid map\n" RESET);
		return (-1);
	}
	*j = fj;
	return 0;
}

int error_not_one(char **map, int *i, int j)
{
	if (j - 1 < 0 || map[*i][j - 1] != '1')
	{
		printf(RED "Error: Invalid map\n" RESET);
		return (-1);
	}
	(*i)++;
	return (0);
}

int	check_left_right(char **map)
{
	int	i;
	int	len;
	int	fj;
	int	j;

	i = 0;
	while (map[i])
	{
		len = (int)ft_strlen(map[i]);
		if (len == 0)
		{
			i++;
			continue ;
		}
		fj = 0;
		while (fj < len && map[i][fj] == ' ')
			fj++;
		if (fj >= len)
		{
			i++;
			continue ;
		}
		if(tile_not_one(map, i, fj, &j) == -1)
			return (-1);
		while (j < len && map[i][j] != ' ')
			j++;
		if(error_not_one(map, &i, j) == -1)
			return -1;
	}
	return (0);
}

int	check_up_down(char **map)
{
	int	j;
	int	len;
	int	i;
	int	fi;

	j = 0;
	len = ft_strlen(map[0]);
	while (j < len)
	{
		fi = 0;
		while (map[fi] && map[fi][j] == ' ')
			fi++;
		if (!map[fi])
		{
			j++;
			continue;
		}
		if (map[fi][j] != '1')
		{
			printf(RED "Error: Invalid map\n" RESET);
			return (-1);
		}
		i = fi;
		while (map[i] && map[i][j] != ' ')
			i++;
		if (i - 1 < 0 || map[i - 1][j] != '1')
		{
			printf(RED "Error: Invalid map\n" RESET);
			return (-1);
		}
		j++;
	}
	return (0);
}

int check_map_copy(char **map_copy, int *i)
{
	*i = 0;
	if (!map_copy)
		return (-1);
	if (check_left_right(map_copy) == -1 || check_up_down(map_copy) == -1 )
	{
		ft_free_map_map(map_copy);
		return (-1);
	}
	return 0;
}

int call_flfl(char **map_copy, int i, int j)
{
	if (flfl(map_copy, i, j))
	{
		printf(RED "Error: Invalid map\n" RESET);
		ft_free_map_map(map_copy);
		return (-1);
	}
	return 0;
}

int	check_map(char **map)
{
	int	i;
	int	j;
	char **map_copy;

	map_copy = copy_map(map);
	if(check_map_copy(map_copy, &i) == -1)
		return -1;
	while (map_copy[i])
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == ' ')
			{
				if(call_flfl(map_copy, i, j) == -1)
					return -1;
			}
			j++;
		}
		i++;
	}
	ft_free_map_map(map_copy);
	return (0);
}

int	check_rgb(int rgb)
{
	if (rgb == -1)
	{
		printf(RED "Error: Invalid RGB value\n" RESET);
		return (-1);
	}
	else if (rgb == -2)
	{
		printf(RED "Error: Missing or duplicate RGB value\n" RESET);
		return (-1);
	}
	return (0);
}
