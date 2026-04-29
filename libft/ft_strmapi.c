/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:41:48 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/29 15:32:56 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))

{
	unsigned int	i;
	char			*str;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	while (i < ft_strlen(s))
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// char	f(unsigned int i, char c)
// {
// 	i = 0;
// 	return (c + 1);
// }

// int	main(void)
// {
// 	char	*str1;
// 	char	*str2;

// 	str1 = "abc";
// 	str2 = ft_strmapi(str1, f);
// 	if (str2 != NULL)
// 	{
// 		printf("%s\n", str2);
// 		free(str2);
// 	}
// 	else
// 	{
// 		printf("error");
// 	}
// 	return (0);
// }