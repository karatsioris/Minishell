/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:33:58 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 15:42:38 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (c);
	else
		return (0);
}

// int	main(void)
// {
// 	char	c;
// 	int		result;

// 	c = '+';
// 	result = ft_isalpha(c);
// 	write(1, &result, sizeof (char));
// 	return (0);
// }
