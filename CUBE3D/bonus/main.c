/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adahab <adahab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:03:24 by waissi            #+#    #+#             */
/*   Updated: 2025/12/25 15:10:55 by adahab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_pointers	*ptrs;
	t_data		img[5];
	t_player	player;
	t_ray		*ray;

	if (ac < 2 || ac > 3)
		return (1);
	ptrs = NULL;
	ray = ft_malloc(&ptrs, (WIDTH / STRIPESIZE) * sizeof(t_ray));
	init_imgs(img);
	init_player(&player);
	if (!treat_map(&player, av[1], &ptrs))
		return (lst_free(&ptrs), 1);
	fill_player(&player, img, &ray, &ptrs);
	mlx_tstart(img);
	init_textures(&player, img);
	mlx_start(&img[0], WIDTH, HEIGHT);
	mlx_hook(img[0].win, 2, 1L << 0, keypress, &player);
	mlx_hook(img[0].win, 3, 1L << 1, key_release, &player);
	mlx_loop_hook(img[0].mlx, loop_hook, &player);
	mlx_loop(img[0].mlx);
}
