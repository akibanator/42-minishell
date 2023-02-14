/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 03:22:51 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/14 01:41:07 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(char *curr_dir, t_env *head)
{
	while (head)
	{
		if (ft_strcmp("PWD", head->name) == 0)
		{
			free(head->value);
			head->value = ft_strdup(curr_dir);
		}
		head = head->next;
	}
}

static void	find_oldpwd(t_env *head, t_env *pos_head)
{
	while (pos_head)
	{
		if (ft_strcmp("OLDPWD", pos_head->name) == 0)
		{
			free(pos_head->value);
			pos_head->value = ft_strdup(head->value);
			break ;
		}
		else if (ft_strcmp("-EOF", pos_head->name) == 0)
		{
			free(pos_head->name);
			pos_head->name = ft_strdup("OLDPWD");
			pos_head->value = ft_strdup(head->value);
			pos_head->next = malloc(sizeof(t_env));
			pos_head->next->name = ft_strdup("-EOF");
			break ;
		}
		pos_head = pos_head->next;
	}
}

static void	update_oldpwd(t_env *head)
{
	t_env	*pos_head;

	pos_head = head;
	while (head)
	{
		if (ft_strcmp("PWD", head->name) == 0)
			find_oldpwd(head, pos_head);
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
		{
			update_oldpwd(head);
			update_pwd(current_dir, head);
		}
		else
		{
			cmd_error("cd: ", str, 0);
			return (1);
		}
	}
	return (0);
}
