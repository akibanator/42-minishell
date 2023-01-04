/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 21:26:17 by akenji-a          #+#    #+#             */
/*   Updated: 2022/12/28 21:38:10 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	current_dir[4096];
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		perror("getcwd() error");
	else
		ft_printf("%s\n", current_dir);
}
