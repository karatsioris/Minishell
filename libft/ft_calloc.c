/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:50:22 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/20 12:05:23 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	tmp = malloc(count * size);
	i = 0;
	if (tmp == NULL)
		return (NULL);
	while (i < (count * size))
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}

// int main() 
// {
//     int *arr = my_calloc(10, sizeof(int));
//     if (arr == NULL)
// }
// 	free(arr); 
//     return 0;