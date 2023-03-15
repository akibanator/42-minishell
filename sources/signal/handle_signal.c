/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:39:14 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/14 13:56:51 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	sig_int_handle(int signal)
{
	(void) signal;
	ft_printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_int_handle_heredoc(int signal)
{
	(void) signal;
	close(STDIN_FILENO);
	close(STDERR_FILENO);
}
