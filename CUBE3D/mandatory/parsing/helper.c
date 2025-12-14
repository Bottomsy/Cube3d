#include "../cub3d.h"

void print_error(int flag)
{
	if (flag == 1)
		printf("Error: Too many players on map\n");
	else if (flag == 2)
		printf("Error: No players found on map\n");
	exit(1);
}

void ft_free(t_player *player)
{
    if (player->ray)
        free(player->ray);

    if (player->map) 
    {
        if (player->map->map) {
            int r = 0;
            while (player->map->map[r])
            {
                free(player->map->map[r]);
                r++;
            }
            free(player->map->map);
        }
        free(player->map);
    }

    if (player->textures) {
        if (player->textures->no)
                 { free(player->textures->no); player->textures->no = NULL; }
        if (player->textures->so)
                 { free(player->textures->so); player->textures->so = NULL; }
        if (player->textures->we)
                 { free(player->textures->we); player->textures->we = NULL; }
        if (player->textures->ea)
                 { free(player->textures->ea); player->textures->ea = NULL; }
                 free(player->textures);
    }

    if (player->img)
    {
        for (int i = 0; i < 5; i++)
        {

            if (player->img[i].img != NULL && player->img[i].mlx != NULL)
                mlx_destroy_image(player->img[i].mlx, player->img[i].img);

            if (player->img[i].win != NULL && player->img[i].mlx != NULL)
                mlx_destroy_window(player->img[i].mlx, player->img[i].win);

            if (player->img[i].mlx != NULL)
                mlx_destroy_display(player->img[i].mlx);

            if (player->img[i].mlx != NULL)
                free(player->img[i].mlx);

            
        }
}
	
}