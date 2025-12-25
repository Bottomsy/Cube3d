/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waissi <waissi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:46:50 by waissi            #+#    #+#             */
/*   Updated: 2024/11/06 15:46:51 by waissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned char	*str;

	if (!s)
		return (NULL);
	str = (unsigned char *)s;
	if (strlen((char *)str) <= start)
	{
		result = malloc(1);
		if (!result)
			return (NULL);
		result[0] = '\0';
		return (result);
	}
	if (len > strlen((char *)str) - start)
		len = strlen((char *)str) - start;
	result = malloc(sizeof(char) * (len) + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, (char *)&str[start], len + 1);
	return (result);
}
