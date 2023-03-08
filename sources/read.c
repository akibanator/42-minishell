/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:25:26 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/06 22:58:29 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_nelson	*read_input(char **cmdline)
{
	char		**aux;
	int			i;
	t_nelson	*node;
	t_nelson	*start;

	i = 0;
	aux = cmdline;
	node = get_node(aux);
	start = node;
	while (node->content[i])
		i++;
	aux += i;
	while(*aux)
	{
		node->next = get_node(aux);
		node = node->next;
		i = 0;
		while (node->content[i])
			i++;
		aux += i;
	}
	ft_free_array(cmdline, (void *)cmdline);
	return (start);
}
