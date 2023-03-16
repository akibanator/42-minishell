/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:07:55 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/16 01:01:08 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void run_adjustments(t_nelson *node, t_hell *hell, size_t i)
{
	char	*str;

	while (node->content[++i])
	{
		if (node->content[i][0] == '\'')
		{
			str = (char *)malloc(2 * sizeof(char));
			str[0] = node->content[i][0];
			str[1] = 0;
			node->content[i] = ft_strtrim(node->content[i], str);
			free(str);
		}
		else if (node->content[i][0] == '\"')
		{
			str = (char *)malloc(2 * sizeof(char));
			str[0] = node->content[i][0];
			str[1] = 0;
			node->content[i] = ft_strtrim(node->content[i], str);
			node->content[i] = expand_variables(node->content[i], hell);
			free(str);
		}
		else
			node->content[i] = expand_variables(node->content[i], hell);
	}
}

void	run_node(t_hell *hell, t_nelson *node, char *envp[])
{
	run_adjustments(node, hell, -1);
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

static void	ft_endline(t_hell *hell, int status)
{
	if (WIFSIGNALED(status))
		hell->exit_code = 128 + status;
	else if (WIFEXITED(status))
		hell->exit_code = WEXITSTATUS(status);
	if (hell->cmd_nbr > 0)
		free (hell->pids);
	if (hell->cmd_nbr > 1)
		close(hell->to_close);
	hell->cmd_nbr = 0;
	hell->here_code = 0;
}

void	run_line(t_hell *hell, t_nelson *node, char *envp[], int i)
{
	t_nelson	*aux;
	int			status;

	status = 0;
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
			waitpid(hell->pids[i], &status, 0);
	ft_endline(hell, status);
}
