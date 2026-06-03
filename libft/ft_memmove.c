/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:48:49 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/18 18:43:50 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*a;
	const char	*b;
	size_t		i;

	a = dst;
	b = src;
	if (a < b)
	{
		i = 0;
		while (i < len)
		{
			a[i] = b[i];
			i++;
		}
	}
	else if (a > b)
	{
		i = len;
		while (i > 0)
		{
			a[i - 1] = b[i - 1];
			i--;
		}
	}
	return (a);
}

// int	main(void)

// {
// 	char	dst_string[] = "Hello world";
// 	char	src_string[] = "abcas";

// 	printf("Before memmove %s\n", dst_string);
// 	ft_memmove(dst_string, src_string, 3);
// 	printf("After memmove %s\n", dst_string);
// 	return (0);
// }
