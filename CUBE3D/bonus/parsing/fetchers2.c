#include "../cub3d.h"

int	check_error(char *info, t_pointers **ptrs, char **path, int *i)
{
	*i = 1;
	if (info[(*i) + 1] != ' ')
	{
		*path = ft_malloc(ptrs, 6);
		ft_strcpy(*path, "Error");
		while (info[*i] != '\n')
			(*i)++;
		(*i)++;
		return (*i);
	}
	return (-2);
}

int	path_not_null(char *info, char **path, int *i)
{
	if ((*path) != NULL)
	{
		(*path) = NULL;
		while (info[*i] != ' ')
			(*i)++;
		(*i)++;
		while (info[*i] != '\n')
			(*i)++;
		return (*i);
	}
	return (-2);
}

int	get_path(char *info, char **path, int *elements, t_pointers **ptrs)
{
	int	i;
	int	k;

	k = 0;
	if (check_error(info, ptrs, path, &i) != -2)
		return (i);
	if (path_not_null(info, path, &i) != -2)
		return (i);
	i++;
	while (info[i + k] != '\n')
		k++;
	(*path) = ft_malloc(ptrs, k + 1);
	k = 0;
	while (info[i] == ' ')
		i++;
	while (info[i] != '\n')
		(*path)[k++] = info[i++];
	(*path)[k] = '\0';
	(*elements)++;
	return (i);
}

int	fetch_recources(t_textures *txtrs, char *info, int *elements,
		t_pointers **ptrs)
{
	int	i;

	i = 0;
	if (info[i] == 'N' && info[i + 1] == 'O')
		i += get_path(info + i, &txtrs->no, elements, ptrs);
	else if (info[i] == 'S' && info[i + 1] == 'O')
		i += get_path(info + i, &txtrs->so, elements, ptrs);
	else if (info[i] == 'W' && info[i + 1] == 'E')
		i += get_path(info + i, &txtrs->we, elements, ptrs);
	else if (info[i] == 'E' && info[i + 1] == 'A')
		i += get_path(info + i, &txtrs->ea, elements, ptrs);
	else if (info[i] == 'C')
		i += get_rgb(info + i, &txtrs->c, elements, ptrs);
	else if (info[i] == 'F')
		i += get_rgb(info + i, &txtrs->f, elements, ptrs);
	return (i);
}

int	extract_num(char *info, int *val, t_pointers **ptrs)
{
	char	*num;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (info[i + k] != '\n' && info[i + k] != ',')
		k++;
	num = ft_malloc(ptrs, k + 1);
	k = 0;
	while (info[i] != '\n' && info[i] != ',')
		num[k++] = info[i++];
	num[k] = '\0';
	k = 0;
	*val = ft_atoi(num);
	if (info[i] == ',')
		i++;
	return (i);
}
