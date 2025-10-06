#include "../includes/cube.h"

int check_format(char *map)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while(map[i])
		i++;
	//error for having no format
	if(i <= 4)
		return (0);
	i -= 4;
	while(FORMAT[k] && map[i])
	{
		//error for not having the wrong format
		if(FORMAT[k] != map[i])
			return (0);
		k++;
		i++;
	}
	return (1);
}

char *read_map(int fd)
{
	char *new;
	char tmp[READSIZE + 1];
	char *final;
	ssize_t b;
	ssize_t bread;

	final = NULL;
	bread = 0;
	b = 0;
	while((b = read(fd, tmp, READSIZE)) > 0)
	{
		tmp[b] = '\0';
		//gay ass malloc failure handling
		new = malloc(b + bread + 1);
		if(bread)
			memcpy(new, final, bread);
		memcpy(new + bread, tmp, b);
		new[b + bread] = '\0';
		bread += b;
		free(final);
		final = new;
	}
	return final;
}

int get_path(char *info, char **path)
{
	int i;
	int k;
	
	i = 0;
	k = 0;
	while(info[i] != ' ')
		i++;
	while(info[i + k] != '\n')
		k++;
	(*path) = malloc(k);
	k = 0;
	while(info[i] != '\n')
		(*path)[k++] = info[i++];
	(*path)[k] = '\0';
	return i;
}

void fill_textures(t_textures *txtrs, char *info)
{
	int i;

	i = 0;
	while(info[i])
	{
		if(info[i] == 'N')
			i += get_path(info + i, &txtrs->no);
		else if(info[i] == 'S')
			i += get_path(info + i, &txtrs->so);
		else if(info[i] == 'W')
			i += get_path(info + i, &txtrs->we);
		else if(info[i] == 'E')
			i += get_path(info + i, &txtrs->ea);
		else if(inf[i] == 'C')
			//set ceiling color
		i++;
	}
}

void split_info(char *info)
{
	//t_map *map;
	t_textures *txtrs;

	//map = malloc(sizeof(t_map));
	txtrs = malloc(sizeof(t_textures));
	fill_textures(txtrs, info);
	printf("%s\n", txtrs->no);
}

int treat_map(char *map)
{
	int fd;

	if(!check_format(map))
		return (0);
	fd = open(map, O_RDONLY);
	printf("%d\n", fd);
	split_info(read_map(fd));
	return (1);
}
