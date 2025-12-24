#include "../cub3d.h"

int lrtile_not_one(char **map, int i, int fj, int *j)
{
        if (map[i][fj] != '1')
        {
                printf(RED "Error: Invalid map\n" RESET);
                return (-1);
        }
        *j = fj;
        return 0;
}

int lr_not_one(char **map, int *i, int j)
{
        if (j - 1 < 0 || map[*i][j - 1] != '1')
        {
                printf(RED "Error: Invalid map\n" RESET);
                return (-1);
        }
        (*i)++;
        return (0);
}

int udtile_not_one(char **map, int *i, int fi, int j)
{
	if (map[fi][j] != '1')
	{
		printf(RED "Error: Invalid map\n" RESET);
		return (-1);
	}
	*i = fi;
	return (0);
}

int ud_not_one(char **map, int i, int *j)
{
        if (i - 1 < 0 || map[i - 1][*j] != '1')
        {
                printf(RED "Error: Invalid map\n" RESET);
                return (-1);
        }
        (*j)++;
        return (0);
}

int init_map_copy(char ***map_copy, char **map, int *i)
{
	*i = 0;
	*map_copy = copy_map(map);
	if (!(*map_copy))
		return (-1);
	if (check_left_right(*map_copy) == -1 || check_up_down(*map_copy) == -1)
	{
		ft_free_map_map(*map_copy);
		return (-1);
	}
	return (0);
}

