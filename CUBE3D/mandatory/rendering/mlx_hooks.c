#include "../cub3d.h"

int can_walk(t_player *player, int px, int py)
{
    int x;
    int y;

    x = px / TILESIZE;
    y = py / TILESIZE;
    if(player->map->map[y][x] == '1')
        return 0;
    return 1;
}
void move_vertical(t_player *player, int x, int y)
{
   if(player->dir == 1)
    {
        x = player->px + cos(player->angle) * 40.9;
        y = player->py + sin(player->angle) * 40.9;
        if(can_walk(player, x, y))
        {
            player->px += cos(player->angle) * 3.9;
            player->py += sin(player->angle) * 3.9;
        }
    }
    if(player->dir == -1)
    {
        x = player->px - cos(player->angle) * 40.9;
        y = player->py - sin(player->angle) * 40.9;
        if(can_walk(player, x, y))
        {
            player->px -= cos(player->angle) * 3.9;
            player->py -= sin(player->angle) * 3.9;
        }
    }
}
void move_player(t_player *player)
{
    int x = 0;
    int y = 0;

    move_vertical(player, x, y);
    if(player->sdir == 1)
    {
        x = player->px + cos(player->angle + (PI / 2)) * 3.9;
        y = player->py + sin(player->angle + (PI / 2)) * 3.9;
        if(can_walk(player, x, y))
        {
            player->px += cos(player->angle + (PI /2)) * 0.9;
            player->py += sin(player->angle + (PI / 2)) * 0.9;
        }
    }
    if(player->sdir == -1)
    {
        x = player->px + cos(player->angle - (PI / 2)) * 3.9;
        y = player->py + sin(player->angle - (PI / 2)) * 3.9;
        if(can_walk(player, x, y))
        {
            player->px += cos(player->angle - (PI /2)) * 0.9;
            player->py += sin(player->angle - (PI / 2)) * 0.9;
        }
    }
}

int	loop_hook(t_player *player)
{
	move_player(player);
    if(player->dor == 1)
        player->angle += 0.019;
    if(player->dor == -1)
        player->angle -= 0.018;
    memset(player->img->addr, 0, HEIGHT * player->img->line_length); //i guess i can to this with mlx_destroy_image
    draw_walls(player, player->ray);
    mlx_put_image_to_window(player->img->mlx, player->img->win, player->img->img, 0, 0);
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
