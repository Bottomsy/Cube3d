#include "../cub3d.h"

int check_len(int *len, char **map, int *i, int *fj)
{
	*len = (int)ft_strlen(map[*i]);
    if (*len == 0)
    {
        (*i)++;
        return (1);
    }
    *fj = 0;
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

int	check_textures(t_textures *texts, t_map *map)
{
	if ((check_valid_path(texts->no) == -1 || check_valid_path(texts->so) == -1
			|| check_valid_path(texts->ea) == -1
			|| check_valid_path(texts->we) == -1)
		|| (check_tformat(texts->no) == -1 || check_tformat(texts->so) == -1
			|| check_tformat(texts->ea) == -1 || check_tformat(texts->we) == -1)
		|| (check_rgb(texts->c) == -1 || check_rgb(texts->f) == -1)
		|| map->map_start == -1)
		return (-1);
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
