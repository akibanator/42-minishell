/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:25:26 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/13 23:05:39 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*edit_input(char *input, int i, int j)
{
	char	*st;

	while (input[++j])
	{
		if (input[j] != input[j - 1] && (input[j] == '<' || input[j] == '>'))
			i++;
		if (input[j] == '|')
			i++;
	}
	st = (char *)ft_calloc((j + i), sizeof(char));
	j = -1;
	i = -1;
	st[++i] = input[++j];
	while (input[++j])
	{
		if ((input[j - 1] == '<' || input[j - 1] == '>') && input[j] == ' ')
			st[++i] = input[j - 1];
		st[++i] = input[j];
		if (ft_is_redirect(&st[i]) && (st[i - 1] != ' ') && st[i - 1] != st[i])
		{
			st[i + 1] = st[i];
			st[i++] = ' ';
		}
	}
	return (st);
}

static int	get_len(char *s)
{
	int		len;
	char	*delim;

	len = 0;
	if (s[0] == '<' || s[0] == '>')
	{
		if (s[0] == s[1])
			len = 1;
		delim = ft_strdup("<|> ");
		while (s[++len])
			if (ft_strchr(delim, s[len]))
				break ;
	}
	if (s[0] != '<' && s[0] != '>')
	{
		delim = ft_strdup("<|>");
		while (s[len])
		{
			if (ft_strchr(delim, s[len]))
				break ;
			len++;
		}
	}
	free(delim);
	return (len);
}

static t_nelson	*get_node(char *s)
{
	t_nelson	*nelson;

	nelson = (t_nelson *)malloc(sizeof(t_nelson));
	nelson->is_done = FALSE;
	nelson->next = NULL;
	if (*s == '|')
		pipe(nelson->pipe);
	while (*s == ' ')
		s++;
	nelson->content = get_content(s);
	return (nelson);
}

t_nelson	*read_input(char *cmdline)
{
	t_nelson	*input;
	t_nelson	*start;
	char		*aux;

	aux = cmdline;
	input = get_node(cmdline);
	start = input;
	if (*cmdline != '|')
		cmdline += get_len(cmdline);
	else
		cmdline++;
	while (*cmdline)
	{
		input->next = get_node(cmdline);
		if (ft_is_redirect(cmdline - 1) && *cmdline == *(cmdline - 1))
			cmdline++;
		input = input->next;
		if (*cmdline != '|')
			cmdline += get_len(cmdline);
		else
			cmdline++;
	}
	free(aux);
	return (start);
}
