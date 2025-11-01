#include "cub3d.h"

void draw_player(t_player *player, int x0, int y0, int radius, int color) // temporary 
{
    int x = radius;
    int y = 0;
    int err = 0;

    my_mlx_pixel_put(player->img, x0, y0, color);
    while (x >= y)
    {
        my_mlx_pixel_put(player->img, x0 + x, y0 + y, color);
        my_mlx_pixel_put(player->img, x0 + y, y0 + x, color);
        my_mlx_pixel_put(player->img, x0 - y, y0 + x, color);
        my_mlx_pixel_put(player->img, x0 - x, y0 + y, color);
        my_mlx_pixel_put(player->img, x0 - x, y0 - y, color);
        my_mlx_pixel_put(player->img, x0 - y, y0 - x, color);
        my_mlx_pixel_put(player->img, x0 + y, y0 - x, color);
        my_mlx_pixel_put(player->img, x0 + x, y0 - y, color);

        y += 1;
        if (err <= 0)
        {
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }

    draw_rays(player, x0, y0);
}

void draw_map(t_data *img, char **map)
{
	int i = 0, j = 0 , x = 0, y = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
                fill_cell(img,img->grid,COLS,ROWS,i,j,0x00FF0000);
            j++;
		}
		i++;
	}
}

void draw_rays(t_player *player, int px, int py)
{
    for (int i = 0; i < 20; i++)
    {
        float ray_angle = player->angle + (i - 10) * 0.1;
        float dx = cos(ray_angle) * 2;
        float dy = sin(ray_angle) * 2;
        
        float x = px;
        float y = py;
        
        for (int step = 0; step < 100; step++)
        {
            if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
                break;
                
            my_mlx_pixel_put(player->img, (int)x, (int)y, 0x0000FF00);
            x += dx;
            y += dy;
        }
    }
}

void draw_square(t_data *img, int x, int y, int len)
{
	int sx = x - (len / 2), sy = y - (len / 2), i = 0;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			my_mlx_pixel_put(img, x + j, y + i, 0x00FFFFFF);
		}
	}
}

int keypress(int code, t_player *player)
{
	if (code == 119)
    {
        player->px += cos(player->angle) * 20;
        player->py += sin(player->angle) * 20;
        // Add bounds checking
        if (player->px < 10) player->px = 10;
        if (player->px > WIDTH - 10) player->px = WIDTH - 10;
        if (player->py < 10) player->py = 10;
        if (player->py > HEIGHT - 10) player->py = HEIGHT - 10;
    }
    else if (code == 115) 
    {
        player->px -= cos(player->angle) * 20;
        player->py -= sin(player->angle) * 20;
        // Add bounds checking
        if (player->px < 10) player->px = 10;
        if (player->px > WIDTH - 10) player->px = WIDTH - 10;
        if (player->py < 10) player->py = 10;
        if (player->py > HEIGHT - 10) player->py = HEIGHT - 10;
    }
    else if (code == 97) // A key
        player->angle -= 0.2; // Rotate left
    else if (code == 100) // D key
        player->angle += 0.2; // Rotate right
    else if (code == 65307) // ESC key
    {
        exit(0);
    }
    
    memset(player->img->addr, 0, HEIGHT * player->img->line_length); //i guess i can to this with mlx_destroy_image
    draw_map(player->img, player->img->map);
    draw_player(player, player->px, player->py, 10, 0x00FF0000);
	draw_grid(player->img, COLS, ROWS, 0x00FFFFFF);
    mlx_put_image_to_window(player->img->mlx, player->img->win, player->img->img, 0, 0);

    return 0;
}

int mouse_move(int x, int y, t_player *player)
{
    int mouse_delta = x - player->last_mouse_x;
    
    player->angle += mouse_delta * 0.005;  

    player->last_mouse_x = x;

    memset(player->img->addr, 0, HEIGHT * player->img->line_length);
    draw_map(player->img, player->img->map);
    draw_player(player, player->px, player->py, 10, 0x00FF0000);
    mlx_put_image_to_window(player->img->mlx, player->img->win, player->img->img, 0, 0);

    return 0;
}

int **create_grid(int rows, int cols)
{
    int **grid = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        grid[i] = malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++)
            grid[i][j] = 0;
    }
    return grid;
}

void draw_vertical_line(t_data *img, int x, int color)
{
    for (int y = 0; y < HEIGHT; ++y)
        my_mlx_pixel_put(img, x, y, color);
}

void draw_horizontal_line(t_data *img, int y, int color)
{
    for (int x = 0; x < WIDTH; ++x)
        my_mlx_pixel_put(img, x, y, color);
}

void fill_cell(t_data *img, int **grid, int rows, int cols, int r, int c, int color)
{
    if (r < 0 || r >= rows || c < 0 || c >= cols) return;
    int cell_w = WIDTH / cols;
    int cell_h = HEIGHT / rows;

    int x0 = c * cell_w + 1;
    int y0 = r * cell_h + 1;
    int x1 = (c + 1) * cell_w - 1;
    int y1 = (r + 1) * cell_h - 1;

    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 >= WIDTH) x1 = WIDTH - 1;
    if (y1 >= HEIGHT) y1 = HEIGHT - 1;

    for (int y = y0; y <= y1; ++y)
        for (int x = x0; x <= x1; ++x)
            my_mlx_pixel_put(img, x, y, color);

    grid[r][c] = 1;
}

void draw_grid(t_data *img, int cols, int rows, int color)
{
    int cell_w = WIDTH / cols;
    int cell_h = HEIGHT / rows;
    for (int c = 0; c <= cols; ++c) {
        int x = c * cell_w;
        if (x >= WIDTH) x = WIDTH - 1;
        draw_vertical_line(img, x, color);
    }
    for (int r = 0; r <= rows; ++r) {
        int y = r * cell_h;
        if (y >= HEIGHT) y = HEIGHT - 1;
        draw_horizontal_line(img, y, color);
    }
}
