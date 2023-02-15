/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:05:56 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/14 17:40:28 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hell	*setup_hell(char *envp[])
{
	t_hell	*hell;

	hell = (t_hell *)malloc(sizeof(t_hell));
	hell->path = get_path(envp);
	hell->std_in = dup(STDIN_FILENO);
	hell->std_out = dup(STDOUT_FILENO);
	hell->pwd = NULL;
	hell->exit_code = 0;
	return (hell);
}

int	set_fds(t_hell *hell, t_nelson *node)
{
	while (node)
	{
		if (node->content[0][0] == '|')
		{
			run_pipe(hell, node);
			return (node->pipe[0]);
		}
		if (ft_is_redirect(node->content[0]))
			run_redirect(hell, node);
		node = node->next;
	}
	return (-2);
}
