#include "../cub3d.h"

void draw_walls(t_player *player, t_ray *ray)
{
    int i;
    int x;
    int y;

    i = 0;
    dda(player, ray);
    while(i < player->ray_num)
    {   
        init_vars(player, ray, i);
        x = (i * STRIPESIZE);
        if(HEIGHT >= player->wh)
            y = (HEIGHT - player->wh) / 2;
        else 
            y = 0;
        render_scene(player, i, x, y);
        i++;
    }
    draw_grid(player, player->img);
    draw_player(player, (player->px / TILESIZE) * 10, (player->py / TILESIZE) * 10, 4, 0xFF0000);
}

void render_scene(t_player *player, int i, int x, int y)
{
    int k;
    int j;
    int color;
    int wh;
    int y2;

    k = 0;
    check_wh(player, &y2, &wh, y);
    while(k < STRIPESIZE)
    {
        render_ceiling(player, x + k, y2);
        j = 0;
        while(j < wh )
        {
            if (player->wh > HEIGHT)
                player->texturey = (((j + (player->wh - HEIGHT) / 2) * TILESIZE) / player->wh);
            else
                player->texturey = ((j * TILESIZE) / player->wh);
            color = shade_color_gamma(pick_text_color(player, i, player->texturex, player->texturey), (100 / player->ray[i].nearest));
            my_mlx_pixel_put(player->img, x + k, y2 + j, color);
            j++;
        }
        render_floor(player, x + k, y2 + j);
        k++;
    }
}

void draw_player(t_player *player, float x0, float y0, int radius, int color) // temporary 
{
    int x = radius;
    int y = 0;
    int err = 0;

    my_mlx_pixel_put(player->img, x0, y0, color);
    while (x >= y)
    {
        my_mlx_pixel_put(player->img, x0 + x, y0 + y, color);
        my_mlx_pixel_put(player->img, x0 + y, y0 + x, color);
        my_mlx_pixel_put(player->img, x0 - y, y0 + x, color);
        my_mlx_pixel_put(player->img, x0 - x, y0 + y, color);
        my_mlx_pixel_put(player->img, x0 - x, y0 - y, color);
        my_mlx_pixel_put(player->img, x0 - y, y0 - x, color);
        my_mlx_pixel_put(player->img, x0 + y, y0 - x, color);
        my_mlx_pixel_put(player->img, x0 + x, y0 - y, color);

        y += 1;
        if (err <= 0)
        {
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }

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
            x = c * MINIMAP_TILESIZE;
            y = r * MINIMAP_TILESIZE;
            if(player->map->map[r][c] == '1')
                draw_square(img, x, y, 0xFFFFFF);
            else if(player->map->map[r][c] == '0' || player->map->map[r][c] == 'E' )
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
    while(i < MINIMAP_TILESIZE - 1)
    {
        j = 1;
        while(j < MINIMAP_TILESIZE - 1)
        {
            my_mlx_pixel_put(img, x + i, y + j, color);
            j++;
        }
        i++;
    }
}
