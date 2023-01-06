/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_is_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:00:02 by rarobert          #+#    #+#             */
/*   Updated: 2022/12/30 03:52:17 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redirect(char *str)
{
	if (!(ft_strncmp(str, "<", 1)))
		return (1);
	if (!(ft_strncmp(str, "<<", 2)))
		return (1);
	if (!(ft_strncmp(str, ">", 1)))
		return (1);
	if (!(ft_strncmp(str, ">>", 2)))
		return (1);
	if (!ft_strncmp(str, "|", 1))
		return (1);
	return (0);
}
