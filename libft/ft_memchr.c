/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:49:13 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 15:43:05 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	cc;
	size_t			i;

	p = (unsigned char *) s;
	cc = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (p[i] == cc)
		{
			return ((void *)(p + i));
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
//     const char	str[] = "a.de";
//     const char	ch = '.';
//     char		*ret;

//     ret = ft_memchr(str, ch, 4);

//     if (ret != NULL) {
//         printf("Character '%c' found at index: %ld\n", ch, (ret - str));
//     } else {
//         printf("Character '%c' not found\n", ch);
//     }
//     return (0);
// }
