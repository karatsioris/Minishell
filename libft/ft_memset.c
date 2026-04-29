/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:48:09 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/13 17:22:37 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*a;
	size_t			i;

	a = b;
	i = 0;
	while (i < len)
	{
		*a++ = (unsigned char)c;
		i++;
	}
	return (b);
}

// int	main(void)

// {
// 	char	string[] = "Hello world";

// 	printf("Before memset %s\n", string);
// 	ft_memset	(string, '#', 4);
// 	printf("After memset %s\n", string);
// 	return (0);
// }
