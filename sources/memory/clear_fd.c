/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 22:39:05 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/03 01:03:43 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_fd(void)
{
	int	fd;

	fd = 100;
	if (fd < 0)
		return ;
	while (fd > STDERR_FILENO)
		close(fd--);
	unlink("tempfile");
}
