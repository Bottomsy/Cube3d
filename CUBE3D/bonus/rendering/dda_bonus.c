/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waissi <waissi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:02:41 by waissi            #+#    #+#             */
/*   Updated: 2025/12/25 18:36:03 by waissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	dda(t_player *player, t_ray *ray)
{
	int		i;
	float	rot_angle;

	i = 0;
	rot_angle = 0;
	while (i < player->ray_num)
	{
		ray[i].angle = (player->angle - (FOV / 2)) + rot_angle;
		normalizeangle(&ray[i].angle);
		hget_step(player, ray, i);
		hget_hit(player, ray, i);
		vget_step(player, ray, i);
		vget_hit(player, ray, i);
		compare_inter(player, ray, i);
		rot_angle += (FOV / player->ray_num);
		i++;
	}
}

void	vget_step(t_player *player, t_ray *ray, int i)
{
	if (ray[i].angle > PI / 2 && ray[i].angle < 3 * PI / 2)
		ray[i].vfirstx = (floor(player->px / TILESIZE) * TILESIZE) - 0.001;
	else
		ray[i].vfirstx = (floor(player->px / TILESIZE) * TILESIZE) + TILESIZE;
	ray[i].vfirsty = player->py + ((ray[i].vfirstx - player->px)
			* tan(ray[i].angle));
	if (ray[i].angle > PI / 2 && ray[i].angle < 3 * PI / 2)
		ray[i].vxstep = -TILESIZE;
	else
		ray[i].vxstep = TILESIZE;
	ray[i].vystep = ray[i].vxstep * tan(ray[i].angle);
}

void	hget_step(t_player *player, t_ray *ray, int i)
{
	if (ray[i].angle > PI)
		ray[i].hfirsty = (floor(player->py / TILESIZE) * TILESIZE) - 0.001;
	else
		ray[i].hfirsty = (floor(player->py / TILESIZE) * TILESIZE) + TILESIZE;
	ray[i].hfirstx = player->px + ((ray[i].hfirsty - player->py)
			/ tan(ray[i].angle));
	if (ray[i].angle > PI)
		ray[i].hystep = -TILESIZE;
	else
		ray[i].hystep = TILESIZE;
	ray[i].hxstep = ray[i].hystep / tan(ray[i].angle);
}

void	hget_hit(t_player *player, t_ray *ray, int i)
{
	ray[i].hhity = ray[i].hfirsty;
	ray[i].hhitx = ray[i].hfirstx;
	while (1)
	{
		if ((ray[i].hhity < 0) || (ray[i].hhitx < 0))
			break ;
		if ((floor(ray[i].hhity / TILESIZE) + 1 >= player->map->rows)
			|| (floor(ray[i].hhitx / TILESIZE) + 1 >= player->map->cols))
			break ;
		if (player->map->map[(int)(floor(ray[i].hhity)
				/ TILESIZE)][(int)floor(ray[i].hhitx) / TILESIZE] == '1')
			break ;
		ray[i].hhity += ray[i].hystep;
		ray[i].hhitx += ray[i].hxstep;
	}
}

void	vget_hit(t_player *player, t_ray *ray, int i)
{
	ray[i].vhity = ray[i].vfirsty;
	ray[i].vhitx = ray[i].vfirstx;
	while (1)
	{
		if ((ray[i].vhity < 0) || (ray[i].vhitx < 0))
			break ;
		if ((floor(ray[i].vhity / TILESIZE) + 1 >= player->map->rows)
			|| (floor(ray[i].vhitx / TILESIZE) + 1 >= player->map->cols))
			break ;
		if (player->map->map[(int)(floor(ray[i].vhity)
				/ TILESIZE)][(int)(floor(ray[i].vhitx) / TILESIZE)] == '1')
			break ;
		ray[i].vhity += ray[i].vystep;
		ray[i].vhitx += ray[i].vxstep;
	}
}
