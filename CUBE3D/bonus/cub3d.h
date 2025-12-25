/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adahab <adahab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:03:14 by waissi            #+#    #+#             */
/*   Updated: 2025/12/25 17:56:06 by adahab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define FORMAT ".cub"
# define TFORMAT ".xpm"
# define READSIZE 10
# define TILESIZE 64
# define MINIMAP_TILESIZE 10
# define PLAYER_COLOR 0xFF0000

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define HEIGHT 900
# define WIDTH 1600
# define FOV 1.0472
# define STRIPESIZE 4
# define PI 3.14159265358979323846
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

typedef struct s_pointers
{
	void				*ptr;
	struct s_pointers	*next;
}						t_pointers;

typedef struct s_textures
{
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	int					c;
	int					f;
	int					elements;
}						t_textures;

typedef struct s_map
{
	char				**map;
	int					map_start;
	int					rows;
	int					cols;
}						t_map;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	char				**map;
	int					**grid;
}						t_data;

typedef struct s_ray
{
	float				hitx;
	float				hity;
	float				vhitx;
	float				vhity;
	float				hhitx;
	float				hhity;
	float				hfirstx;
	float				hfirsty;
	float				vfirstx;
	float				vfirsty;
	float				hxstep;
	float				hystep;
	float				vxstep;
	float				vystep;
	float				length;
	float				angle;
	float				nearest;
}						t_ray;

typedef struct s_player
{
	float				px;
	float				py;
	float				angle;
	float				wall_offset;
	char				dir;
	char				dor;
	char				sdir;
	int					ray_num;
	float				wh;
	int					texturex;
	int					texturey;
	t_data				*img;
	t_map				*map;
	t_ray				*ray;
	t_textures			*textures;
	t_pointers			*ptrs;
}						t_player;

void					mlx_start(t_data *img, int width, int height);
void					mlx_tstart(t_data img[5]);
void					my_mlx_pixel_put(t_data *data, float x, float y,
							int color);
unsigned int			mlx_get_color(t_data *data, int x, int y);
void					my_mlx_xpm_file_to_image(t_data *img, char *path);

void					normalizeangle(float *angle);
void					dda(t_player *player, t_ray *ray);
void					hget_step(t_player *player, t_ray *ray, int i);
void					vget_step(t_player *player, t_ray *ray, int i);
void					hget_hit(t_player *player, t_ray *ray, int i);
void					vget_hit(t_player *player, t_ray *ray, int i);
void					compare_inter(t_player *player, t_ray *ray, int i);

void					draw_grid(t_player *player, t_data *img);
void					draw_walls(t_player *player, t_ray *ray);
void					draw_player(t_player *player, float x0, float y0,
							int radius);
void					render_scene(t_player *player, int i, int x, int y);
void					render_ceiling(t_player *player, int x, int height);
void					render_floor(t_player *player, int x, int y);
int						pick_text_color(t_player *player, int i, int x, int y);
int						shade_color_gamma(int color, float factor);
void					draw_square(t_data *data, int x, int y, int color);

int						keypress(int keycode, t_player *player);
int						key_release(int code, t_player *player);
int						loop_hook(t_player *player);
void					move_player(t_player *player);
void					move_vertical(t_player *player, int x, int y);
int						can_walk(t_player *player, int px, int py);
int						ft_close( t_player *player);

char					**treat_map(t_player *player, char *map,
							t_pointers **ptrs);
void					fill_player(t_player *player, t_data img[5],
							t_ray **ray, t_pointers **ptrs);
int						fill_textures(t_textures *txtrs, char *info,
							t_pointers **ptrs);
int						fill_map(t_map *map, char *info, t_pointers **ptrs);
int						flfl(char **map, int y, int x);
char					**split_info(t_player *player, char *info,
							t_pointers **ptrs);
char					*read_map(int fd, t_pointers **ptrs);
char					**copy_map(char **mapp);
void					create_map(t_map *map, t_pointers **ptrs);
int						coma_return(char *info, int *i, int **rgb);
void					count_cols(char *info, int *cols, int *i);
void					pad_map(t_map *map, char *info, int *i);

int						check_format(char *map);
int						check_tformat(char *map);
int						check_map(char **map);
int						check_left_right(char **map);
int						check_up_down(char **map);
int						check_textures(t_textures *texts, t_map *map);
int						check_rgb(int rgb);
int						check_rgb_values(char *info, int *r, int *g, int *b);
int						check_valid_path(char *path);
int						check_players(char **map);
void					check_only_spaces(char *info, int i, int *only_spaces);
int						check_right(char **map, int i, int fj, int *j);
int						check_left(char **map, int *i, int j);
int						check_down(char **map, int *i, int fi, int j);
int						check_up(char **map, int i, int *j);
int						check_len(int *len, char **map, int *i, int *fj);
int						check_commas_num(char *info);
void					check_wh(t_player *player, int *y2, int *wh, int y);
int						print_error(int flag);

int						get_rows(char *info);
int						get_cols(char *info, t_pointers **ptrs);
int						get_biggest(int *arr, int size);
int						get_path(char *info, char **path, int *elements,
							t_pointers **ptrs);
int						get_rgb(char *info, int *rgb, int *elements,
							t_pointers **ptrs);
int						extract_num(char *info, int *val, t_pointers **ptrs);
void					get_player_info(t_player *player, char **map);
float					get_angle(char d);
int						get_biggest(int *arr, int size);
int						get_path(char *info, char **path, int *elements,
							t_pointers **ptrs);
int						extract_num(char *info, int *val, t_pointers **ptrs);
int						fetch_recources(t_textures *txtrs, char *info,
							int *elements, t_pointers **ptrs);

void					ft_free(t_player *player);
void					ft_free_img(t_data *img);
void					ft_free_map_map(char **map);
void					*ft_malloc(t_pointers **ptrs, size_t size);
void					lst_free(t_pointers **ptrs);
int						lst_new(t_pointers **ptrs, void *ptr);

void					init_player(t_player *player);
void					init_textures(t_player *player, t_data img[5]);
void					init_imgs(t_data img[5]);
void					init_texts(t_textures *txtrs);
int						init_map_copy(char ***map_copy, char **map, int *i);
void					init_rgb(int *r, int *g, int *b, int *i);
void					init_vars(t_player *player, t_ray *ray, int i);

#endif
