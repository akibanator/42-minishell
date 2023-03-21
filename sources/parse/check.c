/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 03:22:36 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/20 14:58:04 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_quotes(char *s, t_hell *hell)
{
	char	quote;
	char	*str;

	str = s;
	while (*s)
	{
		while (*s && *s != '\'' && *s != '\"')
			s++;
		if (*s == '\'' || *s == '\"')
		{
			quote = *s;
			s++;
			while (*s != 0 && *s != quote)
				s++;
			if (*s != quote)
			{
				ft_clear_all(hell);
				cmd_error("", "Please, don't use unclosed quotes\n", 108);
			}
			s++;
		}
	}
	return (str);
}

int	ft_is_builtin(const char *str)
{
	if (!ft_strncmp(str, "echo", 4))
		return (2);
	else if (!ft_strncmp(str, "cd", 2))
		return (1);
	else if (!ft_strncmp(str, "pwd", 3))
		return (2);
	else if (!ft_strncmp(str, "export", 6))
		return (1);
	else if (!ft_strncmp(str, "unset", 5))
		return (1);
	else if (!ft_strncmp(str, "env", 3))
		return (2);
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

int	check_input(char *input)
{
	size_t	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] == '\0')
		return (0);
	if (*input != ' ')
		add_history(input);
	return (1);
}
