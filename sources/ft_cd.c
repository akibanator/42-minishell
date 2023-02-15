/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 03:22:51 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/14 17:48:55 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(char *curr_dir, t_env *head)
{
	while (head)
	{
		if (ft_strcmp(head->name, "PWD") == 0)
		{
			free(head->value);
			head->value = ft_strdup(curr_dir);
		}
		head = head->next;
	}
}

int	ft_cd(char *str, t_env *head)
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
			update_pwd(current_dir, head);
		else
		{
			cmd_error("cd: ", str, 0);
			return (1);
		}
	}
	return (0);
}
