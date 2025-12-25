/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adahab <adahab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:06:40 by waissi            #+#    #+#             */
/*   Updated: 2025/12/25 15:09:50 by adahab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_textures(t_player *player, t_data img[5])
{
	my_mlx_xpm_file_to_image(&img[1], player->textures->no);
	my_mlx_xpm_file_to_image(&img[2], player->textures->so);
	my_mlx_xpm_file_to_image(&img[3], player->textures->ea);
	my_mlx_xpm_file_to_image(&img[4], player->textures->we);
}

void	init_imgs(t_data img[5])
{
	int	i;

	i = 1;
	while (i < 5)
	{
		img[i].mlx = NULL;
		img[i].img = NULL;
		img[i].addr = NULL;
		img[i].win = NULL;
		img[i].map = NULL;
		img[i].grid = NULL;
		i++;
	}
}

void	init_player(t_player *player)
{
	player->px = 0;
	player->py = 0;
	player->angle = 0;
	player->dir = 0;
	player->dor = 0;
	player->sdir = 0;
	player->ray_num = 0;
	player->img = NULL;
	player->ray = NULL;
	player->map = NULL;
	player->textures = NULL;
}

void	init_texts(t_textures *txtrs)
{
	txtrs->no = NULL;
	txtrs->so = NULL;
	txtrs->ea = NULL;
	txtrs->we = NULL;
	txtrs->c = -2;
	txtrs->f = -2;
	txtrs->elements = 0;
}

void	init_rgb(int *r, int *g, int *b, int *i)
{
	*r = -2;
	*g = -2;
	*b = -2;
	*i = 0;
}
