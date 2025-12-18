#ifndef CUB3D_H
#define CUB3D_H

#define FORMAT ".cub"
#define TFORMAT ".xpm"
#define READSIZE 10

#include "../mlx/mlx.h"
#include "./libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>

# define TILESIZE 64
# define HEIGHT 900
# define WIDTH 1600
# define FOV 1.0472
# define STRIPESIZE 4
# define PI 3.14159265358979323846
# define RAY_NUM (WIDTH / STRIPESIZE)
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

typedef struct s_textures
{
	char *no;
	char *so;
	char *we;
	char *ea;
	int c;
	int f;
} t_textures;

typedef struct s_map
{
	char **map;
	int map_start;
	int rows;
	int cols;
} t_map;


typedef struct	s_data {
	void	*mlx;
	void 	*win;
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
	char	**map;
	int	**grid;
}	t_data;

typedef struct s_ray
{
	float	hitx;
	float	hity;
	float	vhitx;
	float	vhity;
	float	hhitx;
	float	hhity;
	float	hfirstx;
	float	hfirsty;
	float	vfirstx;
	float	vfirsty;
	float	hxstep;
	float	hystep;
	float	vxstep;
	float	vystep;
	float	length;
	float	angle;
	float	nearest;
}	t_ray;

typedef struct s_player
{
    float px;
    float py;
    float angle;
    // int last_mouse_x;
    t_data *img;
    char dir;
    char dor;
	char sdir;
    int ray_num;
    t_map *map;
    t_ray *ray;
    t_textures *textures;
}	t_player;

/*                                        MLX HELPER                                                          */
void   mlx_start(t_data *img, int width, int height);
void   mlx_tstart(t_data img[5]);
void   my_mlx_pixel_put(t_data *data, float x, float y, int color);
unsigned int mlx_get_color(t_data *data, int x, int y);
void my_mlx_xpm_file_to_image(t_data *img, char *path);

/*                                        CALCULATING                                                          */
void normalizeangle(float *angle);
void hget_step(t_player *player, t_ray *ray, int i);
void hget_hit(t_player *player, t_ray *ray, int i);
void hdda(t_player *player, t_ray *ray);
void vget_step(t_player *player, t_ray *ray, int i);
void vget_hit(t_player *player, t_ray *ray, int i);
void compare_inter(t_player *player, t_ray *ray, int i);

/*                                        DRAWING FUNCTIONS                                                    */
void draw_vertical_line(t_data *img, int x, int color);
void draw_horizontal_line(t_data *img, int y, int color);
void draw_grid(t_player *player, t_data *img);
void draw_walls(t_player *player, t_ray *ray);
void draw_player(t_player *player, float x0, float y0, int radius, int color);
void draw_square(t_data *data, int x, int y, int color);

/*                                        INPUT HANDLING                                                       */
int   keypress(int keycode, t_player *player);
int key_release(int code, t_player *player);
int loop_hook(t_player *player);
// int mouse_move(int x, int y, t_player *player);

/*                                        MAP PARSING                                                          */
int check_format(char *map);
int check_map(char **map);
int check_left_right(char **map);
int check_up_down(char **map);
char **treat_map(t_player *player, char *map);
int fill_textures(t_textures *txtrs, char *info);
int fill_map(t_map *map, char *info);
int flfl(char **map, int y, int x);
int get_rows(char *info);
int get_cols(char *info);
int get_biggest(int *arr, int size);
int get_path(char *info,  char **path, int *elements);
int get_rgb(char *info,  int *rgb, int *elements);
int extract_num(char *info, int *val);
char **split_info(t_player *player, char *info);
char *read_map(int fd);

/*                                        FREEING                                                              */
void ft_free(t_player *player);
void ft_free_map(t_map *map);
void ft_free_textures(t_textures *textures);
void ft_free_info(char *info);
void ft_free_img(t_data *img);
char **ft_free_parse(t_map *map, t_textures *textures, char *info);

/*                                        INITS                                                                */
void init_player(t_player *player);
void fill_player(t_player *player, t_data img[5], t_ray **ray);
void init_textures(t_player *player, t_data img[5]);
void init_imgs(t_data img[5]);
void init_texts(t_textures *txtrs);

/*                                        MLX HELPER                                                          */
void print_error(int flag);
void get_player_info(t_player *player, char **map);
float get_angle(char d);
int get_biggest(int *arr, int size);


int check_textures(t_textures *texts, t_map *map, char *info);
int check_rgb(int rgb);
int check_valid_path(char *path);
int check_tformat(char *map);


#endif
