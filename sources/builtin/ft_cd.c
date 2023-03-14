/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 03:22:51 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/28 02:46:50 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(char *pwd, t_env *head)
{
	while (head)
	{
		if (ft_strcmp(head->name, "OLDPWD") == 0)
		{
			free(head->value);
			head->value = ft_strdup(pwd);
			return ;
		}
		if (head->next)
			head = head->next;
		else
		{
			head->next = malloc(sizeof(t_env));
			head = head->next;
			head->next = NULL;
			break ;
		}
	}
	head->name = ft_strdup("OLDPWD");
	head->value = ft_strdup(pwd);
}

static void	update_pwd(char *curr_dir, t_env *head)
{
	t_env	*head_pos;

	head_pos = head;
	while (head)
	{
		if (ft_strcmp(head->name, "PWD") == 0)
		{
			update_oldpwd(head->value, head_pos);
			free(head->value);
			head->value = ft_strdup(curr_dir);
			return ;
		}
		head = head->next;
	}
	check_pwd(head_pos);
}

static char	*update_str(t_env *head)
{
	while (head)
	{
		if (ft_strcmp(head->name, "HOME") == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

int	ft_cd(char *str, t_env *head)
{
	char	current_dir[4096];

	if (!str)
		str = update_str(head);
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
