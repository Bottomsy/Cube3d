#include "../cub3d.h"

int	pick_text_color(t_player *player, int i, int x, int y)
{
	if (player->ray[i].hitx == player->ray[i].hhitx
		&& player->ray[i].hity == player->ray[i].hhity)
	{
		if ((player->py - player->ray[i].hity) > 0)
			return (mlx_get_color(&player->img[2], x, y));
		else
			return (mlx_get_color(&player->img[1], x, y));
	}
	else
	{
		if ((player->px - player->ray[i].hitx) > 0)
			return (mlx_get_color(&player->img[4], x, y));
		else
			return (mlx_get_color(&player->img[3], x, y));
	}
}
int	shade_color_gamma(int color, float factor)
{
	int	r;
	int	g;
	int	b;

	if (factor < 0)
		factor = 0;
	if (factor > 1)
		factor = 1;
	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return ((r << 16) | (g << 8) | b);
}
void init_vars(t_player *player, t_ray *ray, int i)
{
    if (ray[i].hitx == ray[i].hhitx && ray[i].hity == ray[i].hhity)
        player->wall_offset = (int)ray[i].hitx % (int)TILESIZE;
    else
        player->wall_offset = (int)ray[i].hity % (int)TILESIZE;
    player->texturex = (int)((player->wall_offset / TILESIZE) * TILESIZE);
    player->wh = (DPP / (ray[i].nearest * cos(ray[i].angle - player->angle))) * TILESIZE;
}

void render_ceiling(t_player *player, int x, int height)
{
    int j;

    j = 0;
    while(j < height)
    {
        my_mlx_pixel_put(player->img, x, j, player->textures->c);
        j++;
    }
}

void render_floor(t_player *player, int x, int y)
{
    while(y < HEIGHT)
    {
        my_mlx_pixel_put(player->img, x, y, player->textures->f);
        y++;
    }
}

void render_scene(t_player *player, int i, int x, int y)
{
    int k;
    int j;
    int color;
    int wh;
    int y2;

    k = 0;
    // int z = 0;
    if (player->wh > HEIGHT)
    {
        wh = HEIGHT;
        y2 = 0;
    }
    else
    {
        wh = player->wh;
        y2 = y;
    }
    while(k < STRIPESIZE)
    {
        render_ceiling(player, x + k, y2);
        j = 0;
        while(j < wh )
        {
            if (player->wh > HEIGHT)
                   player->texturey = (((j + (player->wh - HEIGHT) / 2) * TILESIZE) / player->wh);
            else
            {
                  player->texturey = ((j * TILESIZE) / player->wh);
            }
            color = pick_text_color(player, i, player->texturex, player->texturey);
            color = shade_color_gamma(color, (100 / player->ray[i].nearest));
            my_mlx_pixel_put(player->img, x + k, y2 + j, color);
            j++;
        }
        render_floor(player, x + k, y2 + j);
        k++;
        // z+= 000;
    }
    // mlx_string_put(player->img->mlx, player->img->win,WIDTH/2, HEIGHT/2,0xFFFFFF,ft_itoa((int)player->ray[RAY_NUM/2].hitx / TILESIZE));
    // mlx_string_put(player->img->mlx, player->img->win,WIDTH/2 + 20, HEIGHT/2,0xFFFFFF,ft_itoa((int)player->ray[RAY_NUM/2].hity / TILESIZE));
    // mlx_string_put(player->img->mlx, player->img->win,WIDTH/2, HEIGHT/2 + 20,0xFFFF00,ft_itoa((int)player->px / TILESIZE));
    // mlx_string_put(player->img->mlx, player->img->win,WIDTH/2 + 20, HEIGHT/2 + 20,0xFFFF00,ft_itoa((int)player->py / TILESIZE));
}

void	normalizeangle(float *angle)
{
	*angle = fmod(*angle, 2.0 * PI);
	if (*angle < 0)
		*angle += 2.0 * PI;
}

void	compare_inter(t_player *player, t_ray *ray, int i)
{
	float	vdx;
	float	vdy;
	float	hdx;
	float	hdy;

	vdx = fabs(ray[i].vhitx - player->px);
	vdy = fabs(ray[i].vhity - player->py);
	hdx = fabs(ray[i].hhitx - player->px);
	hdy = fabs(ray[i].hhity - player->py);
	if (sqrt(hdx * hdx + hdy * hdy) < sqrt(vdx * vdx + vdy * vdy))
	{
		ray[i].hitx = ray[i].hhitx;
		ray[i].hity = ray[i].hhity;
		ray[i].nearest = sqrt(hdx * hdx + hdy * hdy);
	}
	else
	{
		ray[i].hitx = ray[i].vhitx;
		ray[i].hity = ray[i].vhity;
		ray[i].nearest = sqrt(vdx * vdx + vdy * vdy);
	}
}



void draw_walls(t_player *player, t_ray *ray)
{
    int i;
    int x;
    int y;

    i = 0;
    hdda(player, ray);
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
