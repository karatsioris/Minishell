/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:50:08 by kkaratsi          #+#    #+#             */
/*   Updated: 2024/04/02 13:06:09 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t		count;
	size_t		is_word;

	count = 0;
	is_word = 0;
	while (*s != '\0')
	{
		if (*s != c && is_word == 0)
		{
			is_word = 1;
			count++;
		}
		else if (*s == c && is_word == 1)
			is_word = 0;
		s++;
	}
	return (count);
}

static char	*word_dup(const char *str, int start, int finish, char c)
{
	char		*word;
	int			word_length;
	const char	*space_ptr;

	if (start < 0 || finish <= start || str[start] == '\0')
		return (NULL);
	space_ptr = ft_strchr(str + start, c);
	if (space_ptr != NULL && space_ptr < str + finish)
	{
		word_length = space_ptr - (str + start);
	}
	else
		word_length = finish - start;
	word = (char *)malloc((word_length + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	ft_strlcpy(word, str + start, word_length + 1);
	word[word_length] = '\0';
	return (word);
}

static void	ft_free_split(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		words[i] = NULL;
		i++;
	}
	free(words);
	words = NULL;
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**words;

	words = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !(words))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			words[j++] = word_dup(s, index, i, c);
			if (words[j - 1] == NULL)
				return (ft_free_split(words), NULL);
			index = -1;
		}
		i++;
	}
	return (words[j] = NULL, words);
}

// int	main(void)
// {
// 	char		**words;
// 	int			i;

// 	words = ft_split("split  ||this|for|me|||||!|", '|');
// if (words == NULL)
// 	{
// 		printf("Memory allocation failed.\n");
// 		return (1);
// 	}
// 	i = 0;
// 	while (words[i] != NULL)
// 	{
// 		printf("%s\n", words[i]);
// 		i++;
// 	}
// 	while (words[i] != NULL)
// 	{
// 		free(words[i]);
// 		i++;
// 	}
// 	free(words);
// 	return (0);
// }
