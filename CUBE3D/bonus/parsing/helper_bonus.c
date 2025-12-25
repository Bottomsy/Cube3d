/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waissi <waissi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:02:17 by waissi            #+#    #+#             */
/*   Updated: 2025/12/25 18:36:03 by waissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	print_error(int flag)
{
	if (flag == 1)
		printf(RED "Error: Too many players on map\n" RESET);
	else if (flag == 2)
		printf(RED "Error: No players found on map\n" RESET);
	return (-1);
}

void	ft_free(t_player *player)
{
	int	i;

	i = 0;
	while (i < 5)
		ft_free_img(&player->img[i++]);
	lst_free(&player->ptrs);
}

void	ft_free_map_map(char **map)
{
	int	r;

	r = 0;
	if (map)
	{
		while (map[r] != NULL)
		{
			free(map[r]);
			r++;
		}
		free(map);
	}
}

void	ft_free_img(t_data *img)
{
	if (img)
	{
		if (img->img != NULL && img->mlx != NULL)
			mlx_destroy_image(img->mlx, img->img);
		if (img->win != NULL && img->mlx != NULL)
			mlx_destroy_window(img->mlx, img->win);
		if (img->mlx != NULL)
			mlx_destroy_display(img->mlx);
		if (img->mlx != NULL)
			free(img->mlx);
	}
}
