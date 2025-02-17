/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 10:15:34 by yel-guad          #+#    #+#             */
/*   Updated: 2025/02/14 10:26:00 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_split(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

static int	count_words(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && (*s == c || *s == '\t'))
			s++;
		if (*s)
			i++;
		while (*s && *s != c && *s != '\t')
			s++;
	}
	return (i);
}

static char	*word_dup(const char *s, int i)
{
	char	*word;

	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	word[i] = '\0';
	while (i--)
		word[i] = s[i];
	return (word);
}

static void	free_all(char **res, int j)
{
	while (j--)
		free(res[j]);
	free(res);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	char	**res;

	j = 0;
	res = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!res)
		return (NULL);
	while (*s)
	{
		while (*s && (*s == c || *s == '\t'))
			s++;
		i = 0;
		while (s[i] && s[i] != c && s[i] != '\t')
			i++;
		if (i)
		{
			res[j] = word_dup(s, i);
			if (!res[j++])
				return (free_all(res, --j), NULL);
			s += i;
		}
	}
	return ((res[j] = NULL), res);
}
