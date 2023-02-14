/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 03:22:51 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/14 13:44:03 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *str, t_env *head)
{
	char	current_dir[4096];

	ft_printf("%s\n", get_value("PWD", head));
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
			cmd_error("cd: ", str, 0);
			return (1);
		}
	}
	return (0);
}
