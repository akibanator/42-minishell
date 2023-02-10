/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:11:17 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/09 22:14:47 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test(char *print, char *error, int flag)
{
	write(2, "minishell: ", 11);
	write(2, print, ft_strlen(print));
	if (flag == 0)
		perror(error);
}