/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:35:04 by rarobert          #+#    #+#             */
/*   Updated: 2023/01/31 21:13:06 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	gen_strlen(char const *str, char delim)
{
	size_t	i;

	i = 0;
	while (str[i] != delim && str[i])
		i++;
	return (i + 1);
}

static size_t	ft_word_counter(char const *s, char c)
{
	size_t	words;
	char	quote;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (*s == '\'' || *s == '\"')
			{
				quote = *s;
				s++;
				while (*s && *s != quote)
					s++;
				if (*s != quote)
					ft_printf("please close all quotes");
			}
			words++;
			while (*s && *s != c)
				s++;
		}	
	}
	return (words);
}

static char	**split_it(char **split, char const *s, char c, size_t words)
{
	size_t	i;
	size_t	j;
	int		len;

	i = 0;
	j = -1;
	while (++j < words)
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\'')
			len = gen_strlen(&s[i + 1], '\'');
		else if (s[i] == '\"')
			len = gen_strlen(&s[i + 1], '\"');
		else
			len = gen_strlen(&s[i], c);
		split[j] = (char *)malloc(sizeof(char) * len);
		if (s[i] == '\'' || s[i] == '\"')
			ft_strlcpy(split[j], &s[i], len);
		else
			ft_strlcpy(split[j], &s[i], len);
		i += len;
	}
	return (split);
}

char	**mini_split(char const *s, char c)
{
	size_t	words;
	char	**split;

	words = ft_word_counter(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	split_it(split, s, c, words);
	if (!split)
	{
		ft_free_array(split, (void *)split);
		return (NULL);
	}
	split[words] = NULL;
	return (split);
}
