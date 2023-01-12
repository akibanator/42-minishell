/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:12:30 by rarobert          #+#    #+#             */
/*   Updated: 2023/01/12 01:29:55 by rarobert         ###   ########.fr       */
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

int	main(void)
{
	t_nelson	*input_list;
	char		*test;
	int			i;
	int			j;

	test = ft_strdup("<test test test2|cmd|cmd2>hi");
	input_list = read_input(edit_input(test, -1, 0));
	j = 0;
	ft_printf("noedit input = %s\n", test);
	ft_printf("edited input = %s\n", edit_input(test, -1, 0));
	while (input_list)
	{
		i = -1;
		while (input_list->content[++i])
			ft_printf("content[%d][%d] = [%s]\n", j, i, input_list->content[i]);
		input_list = input_list->next;
		j++;
	}
}
