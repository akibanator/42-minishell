/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:05:56 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/15 00:51:37 by rarobert         ###   ########.fr       */
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

void	set_fds(t_hell *hell, t_nelson *node)
{
	while (node)
	{
		if (node->content[0][0] == '|')
		{
			run_pipe(hell, node);
			return ;
		}
		if (ft_is_redirect(node->content[0]))
			run_redirect(hell, node);
		node = node->next;
	}
}
