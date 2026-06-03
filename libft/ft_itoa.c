/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:55:50 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 15:35:12 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(long nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			length;
	char		*str;
	const char	*digits;

	digits = "0123456789";
	length = ft_numlen(n);
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	str[length] = '\0';
	if (n == 0)
		str[0] = '0';
	else
		if (n < 0)
			str[0] = '-';
	while (n != 0)
	{
		if (n > 0)
			str[--length] = digits[n % 10];
		else
			str[--length] = digits[n % 10 * -1];
		n /= 10;
	}
	return (str);
}

// int	main(void)
// {
// 	char	*string;

// 	string = ft_itoa(-42);
// 	printf("the number is %s\n", string);
// 	return (0);
// }
