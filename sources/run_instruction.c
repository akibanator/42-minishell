/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:49:26 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/03 01:09:14 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cmd(t_hell *hell, t_nelson *node)
{
	size_t	j;
	char	*cmd;

	if (node->content[0][0] == '.' && node->content[0][0] == '/')
		return (node->content[0]);
	j = 0;
	cmd = ft_strdup(node->content[0]);
	while (hell->path[++j])
	{
		free(node->content[0]);
		node->content[0] = ft_strjoin(hell->path[j], "/");
		node->content[0] = ft_strjoin_free(node->content[0], cmd);
		if (access(node->content[0], 0) == 0)
		{
			free(cmd);
			hell->exit_code = 0;
			return (node->content[0]);
		}
	}
	free (node->content[0]);
	// cmd_error(cmd);
	hell->exit_code = 127;
	return (cmd);
}

void	run_cmd(t_hell *hell, t_nelson *node)
{
	int	i;

	i = 0;
	node->content[0] = get_cmd(hell, node);
	while (hell->pids[i] != 0)
		i++;
	hell->pids[i] = fork();
	sig_setup_exec(hell->pids[i]);
	if (hell->pids[i] == 0)
	{
		close(hell->to_close);
		clear_fd();
		execve(node->content[0], node->content, 0);
		exit(1);
	}
}

void	run_builtin(t_hell *hell, t_nelson *node)
{
	if (!ft_strncmp(node->content[0], "echo", 4))
		ft_echo(node->content);
	else if (!ft_strncmp(node->content[0], "pwd", 3))
		ft_pwd(hell->env);
	else if (!ft_strncmp(node->content[0], "env", 3))
		ft_env(hell->env);
	if (!ft_strncmp(node->content[0], "cd", 2))
		ft_cd(node->content[1], hell->env);
	else if (!ft_strncmp(node->content[0], "export", 6))
		ft_export(node->content[0], hell->env);
	else if (!ft_strncmp(node->content[0], "unset", 5))
		ft_unset(node->content[1], hell->env);
	else if (!ft_strncmp(node->content[0], "exit", 4))
		ft_exit();
}
