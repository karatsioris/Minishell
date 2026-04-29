/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:43:13 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/24 15:33:06 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	p;

	p = c;
	while (*s != '\0')
	{
		if (*s == p)
			return ((char *)s);
		s++;
	}
	if (p == '\0')
		return ((char *)s);
	return (NULL);
}

// int	main(void)
// {
// 	const char	*str = "Hello, World";
// 	char		*ptr;

// 	ptr = ft_strchr(str, 'Z');
// 	if (ptr != NULL)
// 	{
// 		printf("Found at index : %ld\n", ptr - str);
// 	}
// 	else
// 	{
// 		printf("didn't find occurrense at %s", str);
// 	}
// 	return (0);
// }
