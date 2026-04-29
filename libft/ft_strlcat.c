/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:11:57 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/13 17:25:19 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	count;

	dst_len = 0;
	src_len = 0;
	count = 0;
	while (dst[dst_len] != '\0' && dst_len < size)
		dst_len++;
	while (src[src_len])
		src_len++;
	if (size <= dst_len)
		return (size + src_len);
	while (src[count] != '\0' && dst_len + count < size - 1)
	{
		dst[dst_len + count] = src[count];
		count++;
	}
	dst[dst_len + count] = '\0';
	return (dst_len + src_len);
}

// int	main(void)

// {
// 	char	a[8] = "123";
// 	char	b[] = "456";
// 	ft_strlcat(a, b, sizeof (a));
// 	printf("the result of concatenation is: %s\n", a);
// 	printf("the number is: %zu\n", sizeof a);
// 	return (0);
// }
