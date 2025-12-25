/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adahab <adahab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:07:03 by waissi            #+#    #+#             */
/*   Updated: 2025/12/25 15:10:02 by adahab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_ceiling(t_player *player, int x, int height)
{
	int	j;

	j = 0;
	while (j < height)
	{
		my_mlx_pixel_put(player->img, x, j, player->textures->c);
		j++;
	}
}

void	render_floor(t_player *player, int x, int y)
{
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(player->img, x, y, player->textures->f);
		y++;
	}
}

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

void	draw_square(t_data *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 1;
	while (i < MINIMAP_TILESIZE - 1)
	{
		j = 1;
		while (j < MINIMAP_TILESIZE - 1)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
