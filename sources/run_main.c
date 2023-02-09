/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:07:55 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/09 13:51:42 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_node(t_hell *hell, t_nelson *node)
{
	if (node->content[0][0] == '|')
		run_pipe(hell, node);
	else if (ft_is_redirect(node->content[0]))
		run_redirect(hell, node);
	else
	{
		hell->close = set_fds(hell, node);
		if (ft_is_builtin(node->content))
			run_builtin(hell, node);
		else
			run_cmd(hell, node);
	}
}

void	run_line(t_hell *hell, t_nelson *node)
{
	while (node)
	{
		run_node(hell, node);
		node = node->next;
	}
}
