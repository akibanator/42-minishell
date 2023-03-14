/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:07:08 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/14 02:12:59 by rarobert         ###   ########.fr       */
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

char	**get_path(char *envp[])
{
	size_t	i;
	char	*path_arr;

	i = -1;
	while (envp[++i])
		if (!(ft_strncmp("PATH", envp[i], 4)))
			path_arr = envp[i];
	return (ft_split(path_arr, ':'));
}
