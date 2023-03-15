/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:05:56 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/14 23:13:08 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hell	*setup_hell(char *envp[])
{
	t_hell	*hell;

	hell = (t_hell *)malloc(sizeof(t_hell));
	hell->env = init_env(envp);
	hell->path = get_path(hell->env);
	hell->std_in = dup(STDIN_FILENO);
	hell->std_out = dup(STDOUT_FILENO);
	hell->std_err = dup(STDERR_FILENO);
	hell->to_close = -1;
	hell->cmd_nbr = 0;
	hell->lines = 0;
	hell->pwd = NULL;
	hell->exit_code = 0;
	hell->here_code = 0;
	ft_export("?=0", hell->env);
	return (hell);
}

void	set_fds(t_hell *hell, t_nelson *node)
{
	t_nelson	*aux;

	aux = node;
	while (node && node->content[0][0] != '|')
		node = node->next;
	if (node != NULL)
		run_pipe(hell, node);
	node = aux;
	while (node)
	{
		if (node->content[0][0] == '|')
			return ;
		if (ft_is_redirect(node->content[0]))
			run_redirect(node, hell);
		node = node->next;
	}
}
