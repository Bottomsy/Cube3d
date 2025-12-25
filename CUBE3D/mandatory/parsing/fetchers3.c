#include "../cub3d.h"

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
