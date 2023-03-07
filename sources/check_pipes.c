/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 21:28:30 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/06 22:20:45 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pipes(t_nelson *nelson)
{
	if (nelson->content[0][0] == '|')
	{
		cmd_error("syntax error near unexpected token `|'\n", "", 1);
		return ;
	}
	while (nelson)
	{
		if (nelson->next)
			nelson = nelson->next;
	}
	if (nelson->content[0][0] == '|')
	{
		cmd_error("syntax error near unexpected token `|'\n", "", 1);
		return ;
	}
}
