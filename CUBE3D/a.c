#include <stdio.h>
#include <stdlib.h>
#include "./mandatory/libft/libft.h"

int main()
{
	char *num;
	num = malloc(10);
	num = "a    12           ";
	printf("%d", ft_atoi(num));
}
