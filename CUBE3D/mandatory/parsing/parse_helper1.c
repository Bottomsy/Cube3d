#include "../cub3d.h"

int get_path(char *info, char **path, int *elements)
{
	int i;
	int k;
	
	i = 0;
	k = 0;
	while(info[i] != ' ')
		i++;
	i++;
	while(info[i + k] != '\n')
		k++;
	(*path) = malloc(k + 1);
	k = 0;
	while(info[i] != '\n')
		(*path)[k++] = info[i++];
	(*path)[k] = '\0';
	(*elements)++;
	return i;
}

int get_rgb(char *info, unsigned int *rgb, int *elements)
{
	int i;
	unsigned char r;
	unsigned char g;
	unsigned char b;

	i = 0;
	while(info[i] != ' ')
		i++;
	i++;
	i += extract_num(info + i, &r);
	i += extract_num(info + i, &g);
	i += extract_num(info + i, &b);
	(*rgb) = (r << 16) | (g << 8) | b;
	(*elements)++;
	return i;
}

int get_biggest(int *arr, int size)
{
    int i;
    int biggest;

    i = 1;
    biggest = arr[0];
    while(i < size)
    {
        if(biggest < arr[i])
            biggest = arr[i];
        i++;
    }
    return biggest;
}

int get_cols(char *info)
{
    int i;
    int j;
    int col;
    int cols[get_rows(info)];
    j = 0;
    i = 0;
    while(j < get_rows(info))
    {
        col = 0;
        while(info[i] == ' ')
        {
            col++;
            i++;
        }
        while(info[i] && info[i] != '\n' && info[i] != ' ')
        {
            col++;
            i++;
        }
        if(info[i] && info[i] == '\n')
            i++;
        while(info[i] && info[i] == ' ')
            i++;
        if(info[i] && info[i] == '\n')
            i++;
        cols[j++] = col;
    }
    return get_biggest(cols, get_rows(info));
}

int get_rows(char *info)
{
    int i;
    int rows;
    rows = 0;
    i = 0;
    while(info[i])
    {
        if(info[i] == '\n')
            rows++;
        i++;
    }
    if(info[i - 1] != '\n')
        rows++;
    return (rows);
}