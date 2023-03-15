/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:07:08 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/14 23:44:07 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exit_code(t_hell *hell)
{
	char	*exit;
	char	*code;

	exit = ft_strdup("?=");
	code = ft_itoa(hell->exit_code);
	exit = ft_strjoin_free(exit, code);
	ft_export(exit, hell->env);
	free(exit);
	free(code);
}

char	**get_path(t_env *env)
{
	char	*path_arr;
	char	**split;

	path_arr = NULL;
	while (env)
	{
		if (!(ft_strncmp("PATH", env->name, 4)))
			path_arr = env->value;
		env = env->next;
	}
	if (path_arr != NULL)
		split = ft_split(path_arr, ':');
	else
		split = ft_split("a:b:c", ':');
	return (split);
}
