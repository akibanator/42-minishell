/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 23:35:04 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/06 22:23:50 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	gen_strlen(char const *str, char delim)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != delim)
		i++;
	return (i);
}

static size_t	get_redir_len(char const *str, char delim)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != delim && str[i] != '|'
		&& str[i] != '<' && str[i] != '>')
		i++;
	return (i);
}

static size_t	ft_word_counter(char const *s, char c, size_t words, int aux)
{
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (ft_is_redirect(s))
				words++;
			if (ft_is_redirect(s) && *(s + 1) != *s)
				s += 2;
			if (ft_is_redirect(s) && *(s + 1) && *(s + 1) == *s)
				s += 2;
			if (*s == '\'' || *s == '\"')
			{
				aux = gen_strlen(s + 1, *s);
				if (*(s + aux + 1) != *s)
					ft_printf("please close all quotes");
				s += aux + 2;
			}
			words++;
			while (*s && *s != c && *s != '|' && *s != '>' && *s != '<')
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
		if (s[i] == '\'' || s[i] == '\"')
			len = gen_strlen(&s[i + 1], s[i]) + 2;
		else if (ft_is_redirect(&s[i]))
			len = 1;
		else
			len = get_redir_len(&s[i], c);
		if (ft_is_redirect(&s[i]) && s[i + 1] && s[i + 1] == s[i])
			len++;
		split[j] = (char *)malloc(sizeof(char) * (len + 1));
		ft_strlcpy(split[j], &s[i], len + 1);
		i += len;
	}
	split[j] == NULL;
	return (split);
}

char	**mini_split(char const *s, char c)
{
	size_t	words;
	char	**split;

	words = ft_word_counter(s, c, 0, 0);
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
