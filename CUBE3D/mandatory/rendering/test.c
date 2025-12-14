#include "../cub3d.h"

// void draw_player(t_player *player, float x0, float y0, int radius, int color, t_ray *ray) // temporary 
// {
//     int x = radius;
//     int y = 0;
//     int err = 0;

//     my_mlx_pixel_put(player->img, x0, y0, color);
//     while (x >= y)
//     {
//         my_mlx_pixel_put(player->img, x0 + x, y0 + y, color);
//         my_mlx_pixel_put(player->img, x0 + y, y0 + x, color);
//         my_mlx_pixel_put(player->img, x0 - y, y0 + x, color);
//         my_mlx_pixel_put(player->img, x0 - x, y0 + y, color);
//         my_mlx_pixel_put(player->img, x0 - x, y0 - y, color);
//         my_mlx_pixel_put(player->img, x0 - y, y0 - x, color);
//         my_mlx_pixel_put(player->img, x0 + y, y0 - x, color);
//         my_mlx_pixel_put(player->img, x0 + x, y0 - y, color);

//         y += 1;
//         if (err <= 0)
//         {
//             err += 2*y + 1;
//         }
//         if (err > 0)
//         {
//             x -= 1;
//             err -= 2*x + 1;
//         }
//     }

// }

// int mouse_move(int x, int y, t_player *player)
// {
//     int mouse_delta = x - player->last_mouse_x;
    
//     player->angle += mouse_delta * 0.005;  

//     player->last_mouse_x = x;

//     memset(player->img->addr, 0, HEIGHT * player->img->line_length);
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

void draw_grid(t_player *player, t_data *img)
{
	int r;
	int c;
	int x;
	int y;

	r = 0;
	while(r < player->map->rows)
	{
		c = 0;
		while(c < player->map->cols)
		{
			x = c * TILESIZE;
			y = r * TILESIZE;
			if(player->map->map[r][c] == '1')
				draw_square(img, x, y, 0xFFFFFF);
			else if(player->map->map[r][c] == '0')
				draw_square(img, x, y, 0x000000);
			c++;
		}
		r++;
	}
}

void draw_square(t_data *img, int x, int y, int color)
{
	int i;
	int j;

	i = 1;
	while(i < TILESIZE - 1)
	{
		j = 1;
		while(j < TILESIZE - 1)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}