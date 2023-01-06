/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:12:30 by rarobert          #+#    #+#             */
/*   Updated: 2022/12/30 14:52:33 by rarobert         ###   ########.fr       */
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
	delim = ft_strdup("<>| \'\"");
	while (s[len])
	{
		if (ft_strchr(delim, s[len]))
			break ;
		len++;
	}
	free (delim);
	return (len);
}

static char	**get_cmd(char *s)
{
	
}

static t_nelson get_node(char *s)
{
	t_nelson	*nelson;

	nelson = (t_nelson *)malloc(sizeof(t_nelson));
	nelson->is_done = FALSE;
	nelson->next = NULL;
	if (*s == '|')
		pipe(nelson->pipe);
	is_dq = *s == '\"';
	nelson->cmd = get_cmd(*s);
	return (nelson);
}

t_nelson *read_input(char *cmdline)
{
	t_nelson	*input;

	input = get_node(*cmdline);
	cmdline += get_len(*cmdline);
	while (*cmdline)
	{
		input->next = get_node(*cmdline++);
		input = input->next;
		cmdline += get_len(*cmdline);
	}
	return (input);
}

int	main(void)
{
	// t_ *input_list;
	char	*str;
	// char	*list;
	int		len;

	// list = ft_strdup("<>| \'\"");
	str = ft_strdup("abcde<6fgh");
	len = *str == 'a';
	// if (argc != 2)
	// 	return (0);
	// while (str[len])
	// {
	// 	if (ft_strchr(list, str[len]))
	// 		break ;
	// 	len++;
	// }
	ft_printf("len = %d\n", len);
	// check_quotes(str);
	// input_list = read_input(argv[1]);
}
