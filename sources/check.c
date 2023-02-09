/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 03:22:36 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/09 13:53:10 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(char *s)
{
	char	quote;

	while (*s)
	{
		while (*s && *s != '\'' && *s != '\"')
			s++;
		if (*s == '\'' || *s == '\"')
		{
			quote = *s;
			s++;
			while (*s && *s != quote)
				s++;
			if (*s != quote)
			{
				ft_printf("please close all quotes");
				exit(1);
			}
			s++;
		}
	}
}

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
