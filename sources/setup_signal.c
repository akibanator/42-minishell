/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:39:12 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/14 23:59:11 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_setup_prompt(void)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;

	sigemptyset(&sig_int.sa_mask); //zera as mascaras padroes
	sig_int.sa_handler = sig_int_handle; //callback da function handle
	sigaction(SIGINT, &sig_int, NULL); // captura o sigint(CTRL + C) e executa a function handler
	sigemptyset(&sig_quit.sa_mask); //zera as mascaras padroes
	sig_quit.sa_handler = SIG_IGN; // SIG_IGN function para ignorar
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void 	sig_setup_exec(pid_t id)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask); //zera as mascaras padroes
	if (id == 0)
		sig.sa_handler = SIG_DFL; // Quando tiver no processo filho, o signal terá o comportamento padrao
	else
		sig.sa_handler = SIG_IGN; // SIG_IGN function para ignorar
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}
