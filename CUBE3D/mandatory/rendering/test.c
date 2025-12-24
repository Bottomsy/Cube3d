#include "../cub3d.h"



// int mouse_move(int x, int y, t_player *player)
// {
//     int mouse_delta = x - player->last_mouse_x;
    
//     player->angle += mouse_delta * 0.005;  

//     player->last_mouse_x = x;

//     ft_memset(player->img->addr, 0, HEIGHT * player->img->line_length);
//     draw_player(player, player->px, player->py, 10, 0x00FF0000, player->ray);
//     mlx_put_image_to_window(player->img->mlx, player->img->win, player->img->img, 0, 0);

//     return 0;
// }

void draw_vertical_line(t_data *img, int x, int color)
{
    for (int y = 0; y < HEIGHT; ++y)
        my_mlx_pixel_put(img, x, y, color);
}

void draw_horizontal_line(t_data *img, int y, int color)
{
    for (int x = 0; x < WIDTH; ++x)
        my_mlx_pixel_put(img, x, y, color);
}

