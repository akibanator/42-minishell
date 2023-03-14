/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:05:08 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/14 03:27:29 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_nelson(t_nelson *nelson)
{
	t_nelson	*aux;

	while (nelson)
	{
		ft_free_array(nelson->content, (void *)nelson->content);
		aux = nelson;
		nelson = nelson->next;
		free(aux);
	}
}

void	ft_clear_all(t_hell *hell)
{
	rl_clear_history();
	free(hell->pwd);
	free_env(hell->env);
	close(hell->std_in);
	close(hell->std_out);
	close(hell->std_err);
	ft_free_array(hell->path, (void *)hell->path);
	free(hell);
}
