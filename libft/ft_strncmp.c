/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:26:54 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 15:44:40 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	uc1;
	unsigned char	uc2;

	i = 0;
	while (*s1 != '\0' && *s2 != '\0' && i < n)
	{
		uc1 = (unsigned char)*s1;
		uc2 = (unsigned char)*s2;
		if (uc1 != uc2)
			return (uc1 - uc2);
		s1++;
		s2++;
		i++;
	}
	if (i == n)
		return (0);
	else
		return ((unsigned char)*s1 - (unsigned char)*s2);
}

// int	main(void)
// {
// 	char	str1[20] = "Hello World";
// 	char	str2[20] = "HelLo Worlddsd";
// 	int		result;

// 	result = ft_strncmp(str1, str2, 4);
// 	if (result == 0)
// 		printf("Both the strings str1 and str2 are equal");
// 	else if (result < 0)
// 		printf("The first unmatched character of str1 is less than str2");
// 	else
// 		printf("The first unmatched character of str1 is greater than str2");
// 	return (0);
// }
