/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:34:57 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/20 10:50:29 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)

{
	unsigned char		*a;
	const unsigned char	*b;
	size_t				i;

	a = dst;
	b = src;
	i = 0;
	if (a == NULL && b == NULL)
		return (dst);
	while (i < n)
	{
		*a++ = *b++;
		i++;
	}
	return (dst);
}

// int	main(void)

// {
// 	char    dst_string[] = "Hello world";
// 	char    src_string[] = "abc";

// 	printf("Before memcpy %s\n", dst_string);
// 	ft_memcpy(dst_string, src_string, 3);
// 	printf("After memcpy %s\n", dst_string);
// 	return (0);
// }
