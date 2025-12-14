#include "../cub3d.h"


void normalizeangle(float *angle)
{
    *angle = fmod(*angle, 2.0 * PI);
    if (*angle < 0)
        *angle += 2.0 * PI;
}



void compare_inter(t_player *player, t_ray *ray, int i)
{
        float vdx = fabs(ray[i].vhitx - player->px);
        float vdy = fabs(ray[i].vhity - player->py);
        float hdx = fabs(ray[i].hhitx - player->px);
        float hdy = fabs(ray[i].hhity - player->py);
        if(sqrt(hdx * hdx + hdy * hdy) < sqrt(vdx * vdx + vdy * vdy))
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


int shade_color_gamma(int color, float factor)
{
    if (factor < 0) factor = 0;
    if (factor > 1) factor = 1;

    int r = ((color >> 16) & 0xFF)* factor;
    int g = ((color >> 8) & 0xFF) * factor;
    int b =  (color & 0xFF) * factor;

    return (r << 16) | (g << 8) | b;
}

int pick_text_color(t_player *player,int i, int x, int y)
{
	if (player->ray[i].hitx == player->ray[i].hhitx && player->ray[i].hity == player->ray[i].hhity)
	{
		if ((player->py - player->ray[i].hity) > 0)
		return (mlx_get_color(&player->img[2], x ,y));
			else
		return (mlx_get_color(&player->img[1], x ,y));
		
	}
	else
	{
		if ((player->px - player->ray[i].hitx) > 0)
			return (mlx_get_color(&player->img[4], x ,y));
		else
			return (mlx_get_color(&player->img[3], x ,y));

	}

}

void draw_walls(t_player *player, t_ray *ray)
{
    hdda(player, ray);
	int i;
	int j;
	float dpp;
	int wh;
	int x;
	int y;
	int k;

	i = 0;
	dpp = (WIDTH / 2) / tan(FOV/2);
	int texturex = 0;
	int texturey = 0;
	while(i < player->ray_num)
	{
		float wall_offset;
        
        if (ray[i].hitx == ray[i].hhitx && ray[i].hity == ray[i].hhity)
            wall_offset = (int)ray[i].hitx % TILESIZE; // Horizontal wall
        else
            wall_offset = (int)ray[i].hity % TILESIZE; // Vertical wall
        
        
        texturex = (int)((wall_offset / TILESIZE) * TILESIZE);
		wh = (dpp / (ray[i].nearest * cos(ray[i].angle - player->angle))) * TILESIZE;
			
			x = (i * STRIPESIZE);
			if(HEIGHT >= wh)
				y = (HEIGHT - wh) / 2;
			else 
				y = 0;
			k = 0;
			
			while(k < STRIPESIZE)
			{
				j = 0;
				while(j < y)
				{
					my_mlx_pixel_put(player->img, x + k, j, player->textures->c);
					j++;
				}
				j = 0;
				while(j < wh )
				{
					 if (wh > HEIGHT)
                 	   texturey = (((j + (wh - HEIGHT) / 2) * TILESIZE) / wh);
                	else
                  	  texturey = ((j * TILESIZE) / wh);

					int color =  pick_text_color(player,i, texturex, texturey);
					color = shade_color_gamma(color, (100 / ray[i].nearest));
					my_mlx_pixel_put(player->img, x + k, y + j, color);

					j++;
				}
				while( j + y < HEIGHT)
				{
					my_mlx_pixel_put(player->img, x + k, y + j, player->textures->f);
					j++;
				}
			k++;
		}
		i++;
	}
}
