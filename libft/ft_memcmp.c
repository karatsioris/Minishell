/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:11:57 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 15:43:22 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)

{
	const unsigned char	*p1 = s1;
	const unsigned char	*p2 = s2;
	size_t				i;

	i = 0;
	while (i < n)
	{
		if (*p1 != *p2)
		{
			return (*p1 - *p2);
		}
		p1++;
		p2++;
		i++;
	}
	return (0);
}

// int main(void)

// {
// 	const char	str1[] = "AeAlo";
// 	char	str2[] = "AeBlo";
// 	int ret;
// 	ret = ft_memcmp(str1, str2, 3);
// 	if(ret > 0)
// 	{
// 		printf("the %s is bigger from %s", str1, str2);
// 	}
// 	else if (ret < 0)
// 	{
// 		printf("the %s is bigger from %s", str2, str1);
// 	}
// 	else
// 	{
// 		printf("the %s is equal with %s", str1, str2);
// 	}
// 	return(0);
// }