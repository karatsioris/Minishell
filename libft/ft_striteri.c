/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:35:24 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 13:03:30 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))

{
	unsigned int	i;

	i = 0;
	if (s == NULL || f == NULL)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// void	increment_chars(unsigned int index, char *c)
// {
// 	printf("Index: %u, Character: %c\n", index, *c);
// 	if (*c >= 'a' && *c <= 'z')
// 		(*c)++;
// 	else if (*c >= 'A' && *c <= 'Z')
// 		(*c)++;
// }

// int	main(void)
// {
// 	char	str[] = "abc123";

// 	printf("Original string: %s\n", str);
// 	ft_striteri(str, &increment_chars);
// 	printf("Modified string: %s\n", str);
// 	return (0);
// }
