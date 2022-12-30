/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 03:22:51 by akenji-a          #+#    #+#             */
/*   Updated: 2022/12/28 21:24:27 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *str)
{
	char	current_dir[4096];

	if (chdir(str))
	{
		ft_printf("%s: No such file or directory\n", str);
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
