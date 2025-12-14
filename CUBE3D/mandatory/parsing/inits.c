#include "../cub3d.h"

void init_textures(t_player *player, t_data img[5])
{
	my_mlx_xpm_file_to_image(&img[1],player->textures->no);
	my_mlx_xpm_file_to_image(&img[2],player->textures->so);
	my_mlx_xpm_file_to_image(&img[3],player->textures->ea);
	my_mlx_xpm_file_to_image(&img[4],player->textures->we);
}

void init_player(t_player *player, t_data img[5], t_ray **ray)
{
	get_player_info(player, img[0].map);
	player->img = img;
	// player->last_mouse_x = WIDTH / 2;
	player->dir = 0;
	player->dor = 0;
	player->sdir = 0;
	player->ray = *ray;
	player->ray_num = RAY_NUM;
}

void init_imgs(t_data img[5])
{
	for (int i = 1; i < 5; i++)
	{
		img[i].mlx = NULL;
		img[i].img = NULL;
		img[i].addr = NULL;
		img[i].win = NULL;
		img[i].map = NULL;
		img[i].grid = NULL;
	}
}