/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:39:14 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/15 00:01:20 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	sig_int_handle(int signal)
{
	(void) signal;

	ft_printf("\n");
	rl_replace_line("", 1); // trocar buffer da read para vazio ""
	rl_on_new_line(); // chama a function da readline para criar uma linha nova
	rl_redisplay(); // exibe o prompt do readline novamente
}
