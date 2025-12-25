#include "../cub3d.h"

void	init_vars(t_player *player, t_ray *ray, int i)
{
	if (ray[i].hitx == ray[i].hhitx && ray[i].hity == ray[i].hhity)
		player->wall_offset = (int)ray[i].hitx % (int)TILESIZE;
	else
		player->wall_offset = (int)ray[i].hity % (int)TILESIZE;
	player->texturex = (int)((player->wall_offset / TILESIZE) * TILESIZE);
	player->wh = (((WIDTH / 2) / tan(FOV / 2)) / (ray[i].nearest
				* cos(ray[i].angle - player->angle))) * TILESIZE;
}

void	check_wh(t_player *player, int *y2, int *wh, int y)
{
	if (player->wh > HEIGHT)
	{
		*wh = HEIGHT;
		*y2 = 0;
	}
	else
	{
		*wh = player->wh;
		*y2 = y;
	}
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
