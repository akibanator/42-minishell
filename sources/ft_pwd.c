/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 21:26:17 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/28 16:17:03 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*check_pwd(t_env *head)
{
	char	current_dir[4096];

	if (getcwd(current_dir, sizeof(current_dir)))
	{
		while (head)
		{
			if (ft_strcmp(head->name, "PWD") == 0)
				return (head);
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
		head->name = ft_strdup("PWD");
		head->value = ft_strdup(current_dir);
		return (head);
	}
	ft_cd(NULL, head);
	return (check_pwd(head));
}

void	ft_pwd(t_env *head)
{
	t_env	*env_pwd;

	env_pwd = check_pwd(head);
	if (env_pwd)
		ft_printf("%s\n", env_pwd->value);
	else
	{
		cmd_error("pwd: ", "No such file or directory", 0);
		ft_cd(NULL, head);
	}
}
