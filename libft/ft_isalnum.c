/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:11:41 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 15:42:32 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

// int	main(void)
// {
// 	char	c;
// 	int		result;
// 	int		output;

// 	c = '1';
// 	result = ft_isalnum(c);
// 	output = result + '0';
// 	write(1, &output, sizeof (char));
// 	return (0);
// }
