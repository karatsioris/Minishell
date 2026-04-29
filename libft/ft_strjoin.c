/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:11:00 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 15:44:25 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)

{
	char	*new_string;
	size_t	i;
	size_t	j;

	new_string = (char *)malloc
		((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof (char));
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new_string[i + j] = s2[j];
		j++;
	}
	new_string[i + j] = '\0';
	return (new_string);
}

// int	main(void)

// {
// 	char	str1[] = "Hello";
// 	char	str2[] = "World";

// 	printf("%s", ft_strjoin(str1, str2));
// }
