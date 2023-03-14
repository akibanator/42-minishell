/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 03:22:36 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/14 03:28:03 by akenji-a         ###   ########.fr       */
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

int	ft_is_builtin(const char *str)
{
	if (!ft_strncmp(str, "echo", 4))
		return (1);
	else if (!ft_strncmp(str, "cd", 2))
		return (1);
	else if (!ft_strncmp(str, "pwd", 3))
		return (1);
	else if (!ft_strncmp(str, "export", 6))
		return (1);
	else if (!ft_strncmp(str, "unset", 5))
		return (1);
	else if (!ft_strncmp(str, "env", 3))
		return (1);
	else if (!ft_strncmp(str, "exit", 4))
		return (1);
	return (0);
}

int	ft_is_redirect(const char *str)
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

void	check_args(int argc, char *argv[])
{
	(void) argv;
	if (argc != 1)
	{
		ft_printf("Invalid argument\n");
		ft_printf("usage: ./minishell\n");
		exit(1);
	}
}

int	check_input(char **input, t_hell *hell)
{
	char	*str;
	size_t	i;

	i = 0;
	str = *input;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	if (**input != ' ')
		add_history(*input);
	if (ft_strchr(*input, '$'))
	{
		str = expand_variables(*input, hell);
		free(*input);
		*input = str;
	}
	return (1);
}
