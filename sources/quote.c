/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 00:08:48 by rarobert          #+#    #+#             */
/*   Updated: 2022/12/20 22:03:27 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if i = strlen -> regular
// if i != strlen -> 
int	next_size(char *str)
{
	int 	i;

	i = 0;
	if (str[i] == 39)
		while (str[++i] != 39)
			;
	if (*str == 34)
	{
		while (str[++i] != 34)
		{
			if (str[i] == '$')
				ft_printf("handle $");
		}
	}
	if (*str != 39 && *str != 34)
		return (-1);
	return (i - 1);
}
