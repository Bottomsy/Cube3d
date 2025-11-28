#include "cub3d.h"


int	main(void)
{
	t_data	img;
    t_player player;
	img.grid = create_grid(COLS, ROWS);
	img.map = treat_map("test.cub");

	player.px = WIDTH / 2;
	player.py = HEIGHT / 2;
	player.angle = 0.0;
	player.last_mouse_x = WIDTH / 2;
    player.img = &img;
	player.dir = 0;
	player.dor = 0;
	mlx_start(&img);
	
	draw_grid(&img, COLS, ROWS, 0x00FFFFFF);
	draw_map(&img,img.map);
	draw_player(&player, player.px, player.py, 10, 0x00FF0000);

	//mlx_key_hook(img.win,keypress, &player);
	mlx_hook(img.win, 2, 1L<<0, keypress, &player);     // Key press
	mlx_hook(img.win, 3, 1L<<1, key_release, &player);   // Key release
	// mlx_hook(img.win, 6, 1L<<6, mouse_move, &player);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_loop_hook(img.mlx, loop_hook, &player);
	mlx_loop(img.mlx);
}
