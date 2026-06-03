/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:45:01 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 15:42:21 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*a;
	size_t			i;

	a = s;
	i = 0;
	while (i < n)
	{
		*(a + i) = 0;
		i++;
	}
}

// int	main(void)
// {
// 	char	a[10] = "azsxdcfv";
// 	printf("before : %s\n", a);
// 	ft_bzero(a, sizeof(a));
// 	printf("after : %s", a);
// 	return(0);
// }
