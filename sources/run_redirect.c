/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:49:57 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/15 02:23:26 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_pipe(t_hell *hell, t_nelson *node)
{
	if (node->is_done == 2)
		return ;
	if (node->is_done == 0)
	{
		dup2(node->pipe[1], STDOUT_FILENO);
		close(node->pipe[1]);
	}
	if (node->is_done == 1)
	{
		dup2(node->pipe[0], STDIN_FILENO);
		close(STDOUT_FILENO);
		dup(hell->std_out);
		close(hell->std_out);
		hell->std_out = dup(STDOUT_FILENO);
		close(node->pipe[0]);
	}
	node->is_done++;
}

void	run_redirect(t_hell *hell, t_nelson *node)
{
	if (node->is_done)
		return ;
	if (node->content[0][0] == '<')
	{
		// if (hell->std_in != -2)
		// 	close(hell->std_in);
		if ((node->content[0][0]) != node->content[0][1])
			hell->std_in = open(node->content[1], O_RDONLY);
		else
			ft_printf("here_doc");
		dup2(hell->std_in, STDIN_FILENO);
	}
	if (node->content[0][0] == '>')
	{
		// if (hell->std_out != -2)
		// 	close(hell->std_out);
		if ((node->content[0][0]) != node->content[0][1])
			hell->std_out = open(node->content[1],
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			hell->std_out = open(node->content[1],
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		dup2(hell->std_out, STDOUT_FILENO);
	}
	node->is_done++;
}
