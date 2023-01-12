/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:12:30 by rarobert          #+#    #+#             */
/*   Updated: 2023/01/12 15:18:42 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_nelson	*input_list;
	char		*test;
	int			i;
	int			j;

	test = ft_strdup("./minishell test test2|cmd|cmd2>hi");
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
