#include "../cub3d.h"

int	can_walk(t_player *player, int px, int py)
{
	int	x;
	int	y;

	x = px / TILESIZE;
	y = py / TILESIZE;
	if (x + 1 > player->map->cols || y + 1 > player->map->rows || x < 0 || y <= 0)
		return (0);
	return (1);
}

void	move_vertical(t_player *player, int x, int y)
{
	if (player->dir == 1)
	{
		x = player->px + cos(player->angle) * 40.9;
		y = player->py + sin(player->angle) * 40.9;
		if (can_walk(player, x, y))
		{
			player->px += cos(player->angle) * 5.9;
			player->py += sin(player->angle) * 5.9;
		}
	}
	if (player->dir == -1)
	{
		x = player->px - cos(player->angle) * 40.9;
		y = player->py - sin(player->angle) * 40.9;
		if (can_walk(player, x, y))
		{
			player->px -= cos(player->angle) * 5.9;
			player->py -= sin(player->angle) * 5.9;
		}
	}
}

void	move_player(t_player *player)
{
	int	x;
	int	y;

	move_vertical(player, 0, 0);
	if (player->sdir == 1)
	{
		x = player->px + cos(player->angle + (PI / 2)) * 20.9;
		y = player->py + sin(player->angle + (PI / 2)) * 20.9;
		if (can_walk(player, x, y))
		{
			player->px += cos(player->angle + (PI / 2)) * 5.9;
			player->py += sin(player->angle + (PI / 2)) * 5.9;
		}
	}
	if (player->sdir == -1)
	{
		x = player->px + cos(player->angle - (PI / 2)) * 20.9;
		y = player->py + sin(player->angle - (PI / 2)) * 20.9;
		if (can_walk(player, x, y))
		{
			player->px += cos(player->angle - (PI / 2)) * 5.9;
			player->py += sin(player->angle - (PI / 2)) * 5.9;
		}
	}
}
