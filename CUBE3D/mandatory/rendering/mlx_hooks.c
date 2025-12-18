#include "../cub3d.h"

int loop_hook(t_player *player)
{
	if(player->dir == 1)
	{
		player->px += cos(player->angle) * 0.9;
        	player->py += sin(player->angle) * 0.9;
		// if (player->px < 10) player->px = 10;
        // 	if (player->px > WIDTH - 10) player->px = WIDTH - 10;
        // 	if (player->py < 10) player->py = 10;
        // 	if (player->py > HEIGHT - 10) player->py = HEIGHT - 10;
	}
	if(player->dir == -1)
	{
        	player->px -= cos(player->angle) * 0.9;
        	player->py -= sin(player->angle) * 0.9;
		// if (player->px < 10) player->px = 10;
        // 	if (player->px > WIDTH - 10) player->px = WIDTH - 10;
        // 	if (player->py < 10) player->py = 10;
        // 	if (player->py > HEIGHT - 10) player->py = HEIGHT - 10;
	
	}
	if(player->sdir == 1)
    {
        player->px += cos(player->angle + (PI /2)) * 0.9;
            player->py += sin(player->angle + (PI / 2)) * 0.9;
        // if (player->px < 10) player->px = 10;
        //     if (player->px > WIDTH - 10) player->px = WIDTH - 10;
        //     if (player->py < 10) player->py = 10;
        //     if (player->py > HEIGHT - 10) player->py = HEIGHT - 10;
    }
    if(player->sdir == -1)
    {
            player->px += cos(player->angle - (PI / 2)) * 0.9;
            player->py += sin(player->angle - (PI / 2)) * 0.9;
        // if (player->px < 10) player->px = 10;
        //     if (player->px > WIDTH - 10) player->px = WIDTH - 10;
        //     if (player->py < 10) player->py = 10;
        //     if (player->py > HEIGHT - 10) player->py = HEIGHT - 10;
    
    }

	if(player->dor == 1)
		player->angle += 0.009;
	if(player->dor == -1)
		player->angle -= 0.009;
	memset(player->img->addr, 0, HEIGHT * player->img->line_length); //i guess i can to this with mlx_destroy_image
    draw_walls(player, player->ray);
    // draw_grid(player, player->img);
	// draw_player(player, player->px, player->py, 10, 0xFF0000);
    mlx_put_image_to_window(player->img->mlx, player->img->win, player->img->img, 0, 0);
	return (0);
}

int keypress(int code, t_player *player)
{
	if (code == 119)
        player->dir = 1;
    if (code == 115) 
        player->dir = -1;
    if (code == 65361) // A key
        player->dor = -1; // Rotate left
    if (code == 65363) // D key
        player->dor = 1; // Rotate right
    if (code == 97)
        player->sdir = -1;
    if (code == 100)
        player->sdir = 1;
    if (code == 65307) // ESC key
    {
        ft_free(player);
        exit(0);
    }
    return 0;
}

int key_release(int code, t_player *player)
{
    if (code == 119)
        player->dir = 0;
    if(code == 115)
        player->dir = 0;
    if (code == 65361) // A key
        player->dor = 0; // Rotate left
    if (code == 65363) // D key
        player->dor = 0; // Rotate right
    if (code == 97)
        player->sdir = 0;
    if (code == 100)
        player->sdir = 0;
    return (0);
}