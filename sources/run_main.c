/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:07:55 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/03 00:48:57 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_node(t_hell *hell, t_nelson *node)
{
	if (node->content[0][0] == '|')
		run_pipe(hell, node);
	if (ft_is_redirect(node->content[0]))
		run_redirect(hell, node);
	else
	{
		set_fds(hell, node);
		if (ft_is_builtin(node->content[0]))
			run_builtin(hell, node);
		else
			run_cmd(hell, node);
	}
}

void	run_line(t_hell *hell, t_nelson *node)
{
	t_nelson	*aux;
	int			i;

	i = -1;
	hell->pids = (pid_t *)ft_calloc(sizeof(pid_t), hell->cmd_nbr);
	aux = node;
	while (node)
	{
		run_node(hell, node);
		node = node->next;
	}
	ft_free_nelson(aux);
	dup2(hell->std_in, STDIN_FILENO);
	dup2(hell->std_out, STDOUT_FILENO);
	while (++i <= hell->cmd_nbr)
		waitpid(hell->pids[i], NULL, 0);
	hell->cmd_nbr = 0;
	close(hell->to_close);
	// waitpid(hell->child, NULL, 0);
}
