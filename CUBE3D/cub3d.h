#ifndef CUB3D_H
#define CUB3D_H

#define FORMAT ".cub"
#define READSIZE 10

#include "./mlx/mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>

# define HEIGHT 600
# define WIDTH 800
# define COLS 30
# define ROWS 30

typedef struct s_textures
{
	char *no;
	char *so;
	char *we;
	char *ea;
	unsigned int c;
	unsigned int f;
} t_textures;

typedef struct s_map
{
	char **map;
	int map_start;
	int rows;
	int cols;
} t_map;

typedef struct s_datap
{
	t_textures *txrs;
	t_map *map;
} t_datap;

typedef struct	s_data {
	void	*mlx;
	void 	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;


    char    **map;
	int		**grid;
}				t_data;

typedef struct s_player
{
    int px;
    int py;
    float angle;
    int last_mouse_x;
    t_data *img;
}				t_player;



/*                                        MLX HELPER                                                          */
void   mlx_start(t_data *img);
void   my_mlx_pixel_put(t_data *data, int x, int y, int color);

/*                                        DRAWING FUNCTIONS                                                    */
void draw_map(t_data *img, char **map);
void draw_player(t_player *player, int x0, int y0, int radius, int color);
void draw_square(t_data *data, int x, int y, int size);
void draw_rays(t_player *player, int px, int py);

/*                                        INPUT HANDLING                                                       */
int   keypress(int keycode, t_player *player);
int mouse_move(int x, int y, t_player *player);

/*                                        GRID CREATION                                                        */
int  **create_grid(int rows, int cols);
void fill_cell(t_data *img, int **grid, int rows, int cols, int r, int c, int color);
void draw_vertical_line(t_data *img, int x, int color);
void draw_horizontal_line(t_data *img, int y, int color);
void draw_grid(t_data *img, int rows, int cols, int line_color);

/*                                        MAP PARSING                                                         */
char **treat_map(char *map);
int check_format(char *map);

#endif
