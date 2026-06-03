/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:13:23 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 15:42:42 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

// int	main(void)
// {
// 	int		c;
// 	int		result;
// 	char	output;

// 	c = 101;
// 	result = ft_isascii(c);
// 	output = result + '0';
// 	write(1, &output, sizeof(char));
// 	return (0);
// }
