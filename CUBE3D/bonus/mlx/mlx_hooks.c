#include "../cub3d.h"

int	loop_hook(t_player *player)
{
	move_player(player);
	if (player->dor == 1)
		player->angle += 0.068;
	if (player->dor == -1)
		player->angle -= 0.068;
	ft_memset(player->img->addr, 0, HEIGHT * player->img->line_length);
	draw_walls(player, player->ray);
	mlx_put_image_to_window(player->img->mlx, player->img->win,
		player->img->img, 0, 0);
	return (0);
}

int	keypress(int code, t_player *player)
{
	if (code == 119)
		player->dir = 1;
	if (code == 115)
		player->dir = -1;
	if (code == 65361)
		player->dor = -1;
	if (code == 65363)
		player->dor = 1;
	if (code == 97)
		player->sdir = -1;
	if (code == 100)
		player->sdir = 1;
	if (code == 65307)
	{
		ft_free(player);
		exit(0);
	}
	return (0);
}

int	key_release(int code, t_player *player)
{
	if (code == 119)
		player->dir = 0;
	if (code == 115)
		player->dir = 0;
	if (code == 65361)
		player->dor = 0;
	if (code == 65363)
		player->dor = 0;
	if (code == 97)
		player->sdir = 0;
	if (code == 100)
		player->sdir = 0;
	return (0);
}
