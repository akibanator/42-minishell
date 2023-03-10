/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:16:44 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/10 15:41:11 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
# include <signal.h>

void	sig_int_handle(int signal)
{
	(void) signal;
	ft_printf("\nTODO signal(CTRL+C and CTRL+D)\n");
}

void	sig_setup_prompt(void)
{
	struct sigaction	sig_int;

	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = 0;
	sig_int.sa_handler = sig_int_handle;
	sigaction(SIGINT, &sig_int, NULL);
}
