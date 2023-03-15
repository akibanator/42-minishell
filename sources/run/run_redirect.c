/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:49:57 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/14 22:55:28 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_pipe(t_hell *hell, t_nelson *node)
{
	if (node->is_done == 0)
	{
		pipe(node->pipe);
		dup2(node->pipe[1], STDOUT_FILENO);
		close(node->pipe[1]);
		hell->to_close = node->pipe[0];
	}
	if (node->is_done == 1)
	{
		dup2(node->pipe[0], STDIN_FILENO);
		dup2(hell->std_out, STDOUT_FILENO);
		close(node->pipe[0]);
	}
	node->is_done++;
}

void	run_redirect(t_nelson *node, t_hell *hell)
{
	int	fd;

	if (node->is_done)
		return ;
	if (node->content[0][0] == '<')
	{
		if ((node->content[0][0]) != node->content[0][1])
			fd = open(node->content[1], O_RDONLY);
		else
			fd = here_doc(node->content[1], hell);
		dup2(fd, STDIN_FILENO);
	}
	if (node->content[0][0] == '>')
	{
		if ((node->content[0][0]) != node->content[0][1])
			fd = open(node->content[1],
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			fd = open(node->content[1],
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	close (fd);
	node->is_done++;
}
