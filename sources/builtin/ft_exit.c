/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 05:55:46 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/15 01:25:33 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(int exit_code)
{
	//TODO ARGUMENTS
	clear_fd();
	//ft_clear_all(hell);
	exit(exit_code);
}
