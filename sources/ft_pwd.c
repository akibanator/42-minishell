/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 21:26:17 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/14 13:41:14 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*check_pwd(t_env *head)
{
	char	current_dir[4096];

	while (head)
	{
		if (ft_strcmp(head->name, "PWD") == 0)
			return (head);
		head = head->next;
	}
	if (getcwd(current_dir, sizeof(current_dir)))
	{
		head = malloc(sizeof(t_env));
		head->name = ft_strdup("PWD");
		head->value = ft_strdup(current_dir);
		head->next = NULL;
	}
	else
	{
		cmd_error("pwd: ", current_dir, 0);
		return (NULL);
	}
	return (head);
}

void	ft_pwd(t_env *head)
{
	t_env	*env_pwd;

	env_pwd = check_pwd(head);
	if (env_pwd)
		ft_printf("%s\n", env_pwd->value);
}
