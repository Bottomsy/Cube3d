#include "../cub3d.h"

int	print_error(int flag)
{
	if (flag == 1)
		printf(RED "Error: Too many players on map\n" RESET);
	else if (flag == 2)
		printf(RED "Error: No players found on map\n" RESET);
	return -1;
}

void	ft_free(t_player *player)
{
	int	i;

	i = 0;
	if (player->ray)
		free(player->ray);
	ft_free_map(player->map);
	ft_free_textures(player->textures);
	while (i < 5)
		ft_free_img(&player->img[i++]);
}

void ft_free_map_map(char **map)
{
	int r = 0;

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

void	ft_free_map(t_map *map)
{
	ft_free_map_map(map->map);
	if (map)
		free(map);
}

void	ft_free_textures(t_textures *textures)
{
	if (textures)
	{
		if (textures->no)
		{
			free(textures->no);
			textures->no = NULL;
		}
		if (textures->so)
		{
			free(textures->so);
			textures->so = NULL;
		}
		if (textures->we)
		{
			free(textures->we);
			textures->we = NULL;
		}
		if (textures->ea)
		{
			free(textures->ea);
			textures->ea = NULL;
		}
		free(textures);
	}
}

void	ft_free_info(char *info)
{
	if (info)
		free(info);
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

char	**ft_free_parse(t_map *map, t_textures *textures, char *info)
{
	ft_free_map(map);
	ft_free_textures(textures);
	ft_free_info(info);
	return (NULL);
}
