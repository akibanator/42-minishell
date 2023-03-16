/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 05:55:46 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/15 19:50:55 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_hell *hell, char **args)
{
	size_t	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	if (i > 2)
		cmd_error("", "exit: too many arguments\n", 2);
	else
	{
		ft_clear_all(hell);
		clear_fd();
		exit(hell->exit_code);
	}
}
