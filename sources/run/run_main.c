/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:07:55 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/15 00:12:29 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_node(t_hell *hell, t_nelson *node, char *envp[])
{
	if (node->content[0][0] == '|')
		run_pipe(hell, node);
	if (ft_is_redirect(node->content[0]))
		run_redirect(node, hell);
	else
	{
		set_fds(hell, node);
		if (ft_is_builtin(node->content[0]))
			run_builtin(hell, node);
		else
			run_cmd(hell, node, envp);
	}
}

void	run_line(t_hell *hell, t_nelson *node, char *envp[], int i)
{
	t_nelson	*aux;

	if (hell->cmd_nbr > 0)
		hell->pids = (pid_t *)ft_calloc(sizeof(pid_t), hell->cmd_nbr + 1);
	aux = node;
	while (node)
	{
		run_node(hell, node, envp);
		node = node->next;
		if (hell->here_code == 1)
			break ;
	}
	ft_free_nelson(aux);
	dup2(hell->std_in, STDIN_FILENO);
	dup2(hell->std_out, STDOUT_FILENO);
	if (hell->cmd_nbr > 0)
		while (++i <= hell->cmd_nbr)
			waitpid(hell->pids[i], NULL, 0);
	if (hell->cmd_nbr > 0)
		free (hell->pids);
	if (hell->cmd_nbr > 1)
		close(hell->to_close);
	hell->cmd_nbr = 0;
	hell->here_code = 0;
}
