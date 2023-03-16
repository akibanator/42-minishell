/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 05:55:46 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/15 22:07:58 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_hell *hell, char **args, t_nelson *node)
{
	size_t	i;
	int		exit_code;

	i = 0;
	while (args[i] != NULL)
		i++;
	if (i > 2)
		cmd_error("", "exit: too many arguments\n", 2);
	else
	{
		exit_code = hell->exit_code;
		ft_free_nelson(node);
		ft_clear_all(hell);
		clear_fd();
		exit(exit_code);
	}
}
