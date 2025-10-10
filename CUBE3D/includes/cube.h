#ifndef CUBE_H
#define CUBE_H

#define FORMAT ".cub"
#define READSIZE 10

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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

typedef struct s_data
{
	t_textures *txrs;
	t_map *map;
} t_data;

int treat_map(char *map);
int check_format(char *map);

#endif
