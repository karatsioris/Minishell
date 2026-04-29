/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:12:48 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 15:06:16 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)

{
	size_t	a;
	size_t	b;

	a = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[a] != '\0' && a < len)
	{
		b = 0;
		while (haystack[a + b] == needle[b] && a + b < len)
		{
			if (needle[b + 1] == '\0')
				return ((char *)&haystack[a]);
			b++;
		}
		a++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	*haystack;
// 	char	*needle;
// 	char	*result;
// 	size_t	len;

// 	len = 3;
// 	haystack = "abc";
// 	needle = "abcdef";
// 	result = ft_strnstr(haystack, needle, len);
// 	if (result == NULL)
// 	{
// 		printf("Substring not found\n");
// 	}
// 	else
// 	{
// 		printf("Substring found at position: %ld\n", result - haystack);
// 	}
// 	return (0);
// }
