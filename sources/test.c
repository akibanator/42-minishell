/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:12:30 by rarobert          #+#    #+#             */
/*   Updated: 2023/01/11 17:24:33 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free3d(char ***arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		ft_free_array(arr[i], (void *)arr[i]);
		i++;
	}
	free(arr);
}

void	print_3d(char ***arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			ft_printf("arr[%d][%d] = %s\n", i, j, arr[i][j]);
			j++;
		}
		i++;
	}
}

void	check_quotes(char *s)
{
	char	quote;

	while (*s)
	{
		while (*s && *s != '\'' && *s != '\"')
			s++;
		if (*s == '\'' || *s == '\"')
		{
			quote = *s;
			s++;
			while (*s && *s != quote)
				s++;
			if (*s != quote)
			{
				ft_printf("please close all quotes");
				exit(1);
			}
			s++;
		}
	}
}

static int	get_len(char *s)
{
	int	len;
	char *delim;

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
	ft_printf ("len = %d\n", len);
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

static char	**get_pipe(void)
{
	char	**pipe;

	pipe = (char **)malloc(2 * sizeof(char *));
	pipe[0] = ft_strdup("|");
	pipe[1] = NULL;
	return (pipe);
}

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
	ft_printf("redir[1] = [%s]\n", redir[1]);
	redir[2] = NULL;
	return (redir);
}

static char	**get_content(char *s)
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

static t_nelson *get_node(char *s)
{
	t_nelson	*nelson;

	nelson = (t_nelson *)malloc(sizeof(t_nelson));
	nelson->is_done = FALSE;
	nelson->next = NULL;
	if (*s == '|')
		pipe(nelson->pipe);
	while (*s == ' ')
		s++;
	nelson->content= get_content(s);
	return (nelson);
}

t_nelson *read_input(char *cmdline)
{
	t_nelson	*input;
	t_nelson	*start;

	input = get_node(cmdline);
	start = input;
	ft_printf("input = %s\n", cmdline);
	if (*cmdline != '|')
		cmdline += get_len(cmdline);
	else
		cmdline++;
	while (*cmdline)
	{
		ft_printf("input = %s\n", cmdline);
		input->next = get_node(cmdline);
		if (ft_is_redirect(cmdline - 1) && *cmdline == *(cmdline - 1))
			cmdline++;
		input = input->next;
		if (*cmdline != '|')
			cmdline += get_len(cmdline);
		else
			cmdline++;
	}
	return (start);
}

char	*edit_input(char *input)
{
	int		i;
	int		j;
	char	*edit;

	i = -1;
	j = 0;
	while (input[++j])
	{
		if(input[j] != input[j - 1] && (input[j] == '<' || input[j] == '>'))
			j++;
		if(input[j] == '|')
			j++;
	}
	edit = (char *)malloc((j + 1) * sizeof(char));
	j = -1;
	edit[++i] = input[++j];
	while (input[++j])
	{
		if ((input[j - 1] == '<' || input[j - 1] == '>') && input[j] == ' ')
			j++;
		edit[++i] = input[j];
		if (edit[i] == '|' || edit[i] == '<' || edit[i] == '>')
		{
			if (edit[i - 1] != ' ')
			{
				edit[i + 1] = edit[i];
				edit[i++] = ' ';
			}
		}
	}
	return (edit);
}

int	main(void)
{
	t_nelson *input_list;
	char	*test;
	int		i;
	int		j;

	test = ft_strdup("<test test test2|cmd|cmd2>hi");
	input_list = read_input(edit_input(test));
	j = 0;
	ft_printf("noedit input = %s\n", test);
	ft_printf("edited input = %s\n", edit_input(test));
	// ft_printf("len = %d\tstr = %s\n", get_len(test), get_str(test + 1));
	// ft_printf("len = %d\tstr = %s\n", get_len(test + 7), get_str(test + 8));
	// ft_printf("len = %d\tstr = %s\n", get_len(test + 7), get_str(test + 13));
	// ft_printf("len = %d\tstr = %s\n", get_len(test + 7), get_str(test + 24));
	// ft_printf("len = %d\tstr = %s\n", get_len(test + 35), get_str(test + 36));
	// ft_printf("len = %d\tstr = %s\n", get_len(test + 7), get_str(test + 24));
	while (input_list)
	{
		i = -1;
		while (input_list->content[++i])
			ft_printf("content[%d][%d] = [%s]\n", j, i, input_list->content[i]);
		input_list = input_list->next;
		j++;
	}
	// input_list = read_input(argv[1]);
}
