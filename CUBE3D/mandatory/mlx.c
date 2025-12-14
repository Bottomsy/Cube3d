#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, float x, float y, int color)
{
	char	*dst;
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        	return;	
	dst = data->addr + ((int)y * data->line_length + (int)x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void mlx_start(t_data *img, int width,int  height)
{
	img->mlx = mlx_init();
        img->win = mlx_new_window(img->mlx, width, height, "test");
        img->img = mlx_new_image(img->mlx, width, height);
        img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
                                                                &img->endian);
}

void mlx_tstart(t_data img[5])
{
	int i = 1;
	while (i < 5)
	{
		img[i].mlx = mlx_init();
		img[i].img = NULL;
		img[i].addr = NULL;
		img[i].win = NULL;
		img[i].map = NULL;
		img[i].grid = NULL;
		i++;
	}
}

unsigned int mlx_get_color(t_data *data, int x, int y)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    return *(unsigned int *)dst;
}

void my_mlx_xpm_file_to_image(t_data *img, char *path)
{
	int x;
	int y;
	img->img = mlx_xpm_file_to_image(img->mlx, path, &x, &y );
	img->addr = mlx_get_data_addr(img->img , &img->bits_per_pixel, &img->line_length, &img->endian);
}
