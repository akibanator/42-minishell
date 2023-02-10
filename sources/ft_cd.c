/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 03:22:51 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/09 22:16:46 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *str)
{
	char	current_dir[4096];

	if (chdir(str))
	{
		cmd_error("cd: ", str, 0);
		return (1);
	}
	else
	{
		if (getcwd(current_dir, sizeof(current_dir)))
			ft_printf("Current directory is: %s\n", current_dir);
		else
		{
			ft_printf("getcwd() error");
			return (1);
		}
	}
	return (0);
}
