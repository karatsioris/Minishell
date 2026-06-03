/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:38:13 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 15:44:49 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurrence;
	char	p;

	p = c;
	last_occurrence = NULL;
	while (*s != '\0')
	{
		if (*s == p)
			last_occurrence = ((char *)s);
		s++;
	}
	if (*s == p)
		last_occurrence = ((char *)s);
	return (last_occurrence);
}

// int	main(void)
// {
// 	const char	*str = "Hello World";
// 	char		*ptr;

// 	ptr = ft_strrchr(str, 'l');
// 	if (ptr != NULL)
// 		printf("The last occurrence find in the index %ld:", ptr - str);
// 	else if (ptr == NULL)
// 	{
// 		printf("In the sentense '%s' didn't find occurrence", str);
// 	}
// 	return (0);
// }
