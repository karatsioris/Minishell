/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:18:33 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 15:42:51 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

// int	main(void)

// {
// 	int		c;
// 	int		result;
// 	char	output;

// 	c = '\n';
// 	result = ft_isprint(c);
// 	output = result + '0';
// 	write (1, &output, sizeof(char));
// 	return (0);
// }
