/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:25:26 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/16 01:03:07 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_nelson	*read_input(char *cmdline, t_hell *hell)
{
	char		**aux;
	int			j;
	int			i;
	t_nelson	*node;
	t_nelson	*start;

	i = 0;
	aux = split_nelson(check_quotes(cmdline, hell), ' ');
	node = get_node(aux, hell);
	start = node;
	while (node->content[i])
		i++;
	while (aux[i])
	{
		node->next = get_node(&aux[i], hell);
		node = node->next;
		j = 0;
		while (node->content[j])
			j++;
		i += j;
	}
	ft_free_array(aux, (void *)aux);
	return (start);
}
