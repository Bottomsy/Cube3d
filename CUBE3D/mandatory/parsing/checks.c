#include "../cub3d.h"

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

int check_boundaries(char **map)
{
	int i = 0;
	while (map[i])
	{
        int len = (int)strlen(map[i]);
        if (len == 0){i++; continue;}

        int fj = 0;
        while (fj < len && map[i][fj] == ' ')
            fj++;

        if (fj >= len)
        {i++; continue;}

        if (map[i][fj] != '1')
        {
            printf("Invalid map\n");
            return -1;
			// exit(0);
        }

        int j = fj;
        while (j < len && map[i][j] != ' ')
            j++;

        if (j - 1 < 0 || map[i][j - 1] != '1')
        {
            printf("Invalid map\n");
            return -1;
			// exit(0);
        }
		i++;
    }
    return 0;
}
int check_map(char **map)
{
    int i = 0, j;
	if(check_boundaries(map) == -1)
        return -1;
	while ( map[i])
    {
        j = 0;
        while ( map[i][j])
        {
            if ( map[i][j] == ' ')
            {

                if (flfl(map, i, j))
                {

                    printf("Invalid map\n");
                    return -1;
                }
            }
            j++;
        }
        i++;
    }
    return 0;
}