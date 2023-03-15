/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:25:26 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/15 17:10:59 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_nelson	*read_input(char *cmdline, t_hell *hell)
{
	char		**aux;
	int			i;
	t_nelson	*node;
	t_nelson	*start;

	i = 0;
	aux = mini_split(check_quotes(cmdline, hell), ' ');
	node = get_node(aux, hell);
	start = node;
	while (node->content[i])
		i++;
	while (aux[i])
	{
		node->next = get_node(&aux[i], hell);
		node = node->next;
		i = 0;
		while (node->content[i])
			i++;
	}
	ft_free_array(aux, (void *)aux);
	return (start);
}
