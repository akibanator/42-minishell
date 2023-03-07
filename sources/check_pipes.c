/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:28:30 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/06 23:05:06 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_node(char content)
{
	if (content == '|')
	{
		cmd_error("syntax error near unexpected token `|'\n", "", 1);
		return (1);
	}
	return (0);
}

void	check_pipes(t_nelson *nelson)
{
	if (check_node(nelson->content[0][0]))
		return ;
	while (nelson)
	{
		if (nelson->next)
			nelson = nelson->next;
	}
	if (check_node(nelson->content[0][0]))
		return ;
}
