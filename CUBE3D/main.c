#include "includes/cube.h"

int main(int ac, char **av)
{
	if(ac != 2)
		return (1);
	treat_map(av[1]);
	return (0);
}
