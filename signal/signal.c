/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:16:44 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/10 15:49:54 by akenji-a         ###   ########.fr       */
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

void	sig_setup_default(void)
{
	struct sigaction	sig_int;

	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = 0;
	sig_int.sa_handler = SIG_DFL; //SIG_DFL existe dentro do signal.h e a gente passa ele no handler para nosso handler ficar com o comportamento padrao dos sinais que a gente quer, no caso o sig_int que a gente tinha mudado antes
	sigaction(SIGINT, &sig_int, NULL);
}