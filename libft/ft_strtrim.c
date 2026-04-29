/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:42:10 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/03/30 16:21:09 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*new_str;

	if (*set == '\0' || *s1 == '\0')
	{
		new_str = ft_strdup(s1);
		return (new_str);
	}
	start = 0;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[end]) && end > start)
		end--;
	new_str = ft_substr(s1, start, (end + 1) - start);
	return (new_str);
}

// int	main(void)
// {
// 	char	*set;
// 	char	*trimmed;

// 	set = "-.!+";
// 	trimmed = ft_strtrim("+!!+-012-3674-+-", set);
// 	printf("Trimmed string:%s\n", trimmed);
// 	return (0);
// }
