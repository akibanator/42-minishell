/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:00:16 by akenji-a          #+#    #+#             */
/*   Updated: 2022/12/27 21:01:19 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char	**str)
{
	if (!ft_strncmp(str[0], "echo", 4))
		return (1);
	else if (!ft_strncmp(str[0], "cd", 2))
		return (1);
	else if (!ft_strncmp(str[0], "pwd", 3))
		return (1);
	else if (!ft_strncmp(str[0], "export", 6))
		return (1);
	else if (!ft_strncmp(str[0], "unset", 5))
		return (1);
	else if (!ft_strncmp(str[0], "env", 3))
		return (1);
	else if (!ft_strncmp(str[0], "exit", 4))
		return (1);
	return (0);
}
