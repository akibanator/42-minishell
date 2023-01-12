/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 04:08:37 by rarobert          #+#    #+#             */
/*   Updated: 2023/01/12 01:29:47 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_str(char *s, char *delim)
{
	int		size;
	int		i;
	int		j;
	char	*str;

	size = 0;
	i = -1;
	j = 0;
	while (s[size] && !(ft_strchr(delim, s[size])))
		if (s[size] != '\'' && s[size] != '\"')
			size++;
	str = (char *)malloc((size + 1) * sizeof(char));
	while (++i < size)
	{
		if (s[j] == '\'' || s[j] == '\"')
			j++;
		str[i] = s[j++];
	}
	str[i] = 0;
	return (str);
}

static char	**get_pipe(void)
{
	char	**pipe;

	pipe = (char **)malloc(2 * sizeof(char *));
	pipe[0] = ft_strdup("|");
	pipe[1] = NULL;
	return (pipe);
}

static char	**get_cmd(char *s)
{
	char	*str;
	char	**cmd;

	while (*s == ' ')
		s++;
	str = get_str(s, "<|>");
	cmd = mini_split(str, ' ');
	free(str);
	return (cmd);
}

static char	**get_redirect(char *s)
{
	char	**redir;

	redir = (char **)malloc(3 * sizeof(char *));
	if ((*s + 1) == *s)
	{
		redir[0] = (char *)malloc(3 * sizeof(char));
		redir[0][0] = *s++;
		redir[0][1] = *s++;
		redir[0][2] = 0;
	}
	else
	{
		redir[0] = (char *)malloc(2 * sizeof(char));
		redir[0][0] = *s++;
		redir[0][1] = 0;
	}
	while (*s == ' ')
		s++;
	redir[1] = get_str(s, "<|> ");
	redir[2] = NULL;
	return (redir);
}

char	**get_content(char *s)
{
	char	**content;

	if (*s == '|')
		content = get_pipe();
	else if (ft_is_redirect(s))
		content = get_redirect(s);
	else
		content = get_cmd(s);
	return (content);
}
