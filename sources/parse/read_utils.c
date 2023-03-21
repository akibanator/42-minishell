/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 04:08:37 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/20 14:39:39 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_pipe(void)
{
	char	**pipe;

	pipe = (char **)malloc(2 * sizeof(char *));
	pipe[0] = ft_strdup("|");
	pipe[1] = NULL;
	return (pipe);
}

static char	**get_redirect(char **s)
{
	char	**redir;

	redir = (char **)malloc(3 * sizeof(char *));
	redir[0] = ft_strdup(*(s++));
	redir[1] = ft_strdup(*s);
	redir[2] = NULL;
	return (redir);
}

static char	**get_cmd(char **s)
{
	int		i;
	char	**cmd;

	i = -1;
	while (s[++i])
		if (ft_is_redirect(s[i]))
			break ;
	cmd = (char **)ft_calloc(i + 1, sizeof(char *));
	while (--i >= 0)
		cmd[i] = ft_strdup(s[i]);
	return (cmd);
}

static char	**get_content(char **s, t_hell *hell)
{
	char	**content;

	if (**s == '|')
		content = get_pipe();
	else if (ft_is_redirect(*s))
		content = get_redirect(s);
	else
	{
		content = get_cmd(s);
		if (ft_is_builtin(content[0]) != 1)
			hell->cmd_nbr++;
	}
	return (content);
}

t_nelson	*get_node(char **s, t_hell *hell)
{
	t_nelson	*nelson;

	nelson = (t_nelson *)malloc(sizeof(t_nelson));
	nelson->is_done = FALSE;
	nelson->next = NULL;
	nelson->content = get_content(s, hell);
	return (nelson);
}
