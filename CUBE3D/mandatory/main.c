#include "cub3d.h"


int	main(int ac, char **av)
{
	t_data	img[5];
	t_player player;
	t_ray *ray;

	if(ac < 2 || ac > 3)
		return (1);

	ray = malloc(RAY_NUM * sizeof(t_ray));
	init_imgs(img);
	img[0].map = treat_map(&player, av[1]);
	if (img[0].map == NULL || check_map(img[0].map) == - 1 || ray == NULL)
	{
		ft_free(&player);
		free(ray);
		return (1);
	}
	
	
	init_player(&player, img, &ray);
	mlx_tstart(img);
	init_textures(&player, img);
	mlx_start(&img[0], WIDTH, HEIGHT);

	mlx_hook(img[0].win, 2, 1L<<0, keypress, &player);     // Key press
	mlx_hook(img[0].win, 3, 1L<<1, key_release, &player);   // Key release
	mlx_loop_hook(img[0].mlx, loop_hook, &player);

	mlx_loop(img[0].mlx);
}
