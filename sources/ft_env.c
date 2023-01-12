/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:50:43 by akenji-a          #+#    #+#             */
/*   Updated: 2023/01/12 02:47:30 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env)
{
	while (ft_strncmp(env->name, "-EOF", 4) != 0)
	{
		ft_printf("%s\n", env->name_value);
		env = env->next;
	}
}
