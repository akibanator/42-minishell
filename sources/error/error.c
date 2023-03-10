/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:11:17 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/07 23:08:43 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_error(char *print, char *error, int flag)
{
	write(2, "minishell: ", 11);
	if (flag == 0)
	{
		write(2, print, ft_strlen(print));
		perror(error);
	}
	if (flag == 127)
	{
		write(2, error, ft_strlen(error));
		write(2, ": command not found\n", 21);
	}
}
