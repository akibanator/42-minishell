/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:19:43 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/01 21:50:48 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*first_node(t_env *env)
{

}

void	*unset_node(t_env *env)
{

}

void	ft_unset(char *str, t_env *head)
{
	int	node_pos;

	node_pos = 0;
	if (str == NULL)
		return ;
	while (head)
	{
		if (!(ft_strcmp(head->name, str)) && node_pos == 0)
		{
			first_node(head);
			break ;
		}
		if (!(ft_strcmp(head->name, str)) && node_pos == 1)
		{
			unset_node(head);
			break ;
		}
		node_pos = 1;
		head = head->next;
	}
}
