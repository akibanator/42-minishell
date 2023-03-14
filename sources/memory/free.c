/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:05:08 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/09 13:58:34 by rarobert         ###   ########.fr       */
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
