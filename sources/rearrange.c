/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 04:08:37 by rarobert          #+#    #+#             */
/*   Updated: 2022/12/28 11:16:11 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	counter(char **input)
{
	int	i;

	i = 1;
	while (*input)
	{
		if (!(ft_strncmp(*input, "<", 1)) || !(ft_strncmp(*input, "<<", 2))
			|| !(ft_strncmp(*input, ">", 1)) || !(ft_strncmp(*input, ">>", 2)))
		{
			i++;
			input++;
		}
		else if (!(ft_strncmp(*input, "|", 1)))
			i += 2;
		input++;
	}
	return (i);
}

char	**get_cmd(char **input)
{
	char	**cmd;
	int		i;

	i = 0;
	while (input[i] && !ft_is_redirect(input[i])
		&& (ft_strncmp(input[i], "|", 1)))
		i++;
	cmd = (char **)malloc((i + 1) * sizeof(char *));
	cmd[i] = NULL;
	while (--i >= 0)
		cmd[i] = *(input + i);
	return (cmd);
}

char	**get_redirect(char **input)
{
	char	**redirect;

	if (input[0][0] == '|')
	{
		redirect = (char **)malloc(2 * sizeof(char *));
		redirect[0] = "|";
		redirect[1] = NULL;
		return (redirect);
	}
	redirect = (char **)malloc(3 * sizeof(char *));
	redirect[0] = *input;
	input++;
	redirect[1] = *input;
	redirect[2] = NULL;
	return (redirect);
}

char	***rearrange_input(char **input)
{
	char	***arranged;
	int		i;

	i = 0;
	arranged = (char ***)malloc(sizeof(char **) * (counter(input) + 1));
	while (*input)
	{
		if (ft_is_redirect(*input) || !ft_strncmp(*input, "|", 1))
			arranged[i] = get_redirect(input);
		else
			arranged[i] = get_cmd(input);
		input++;
		while ((*input && !ft_is_redirect(*input))
			&& (ft_strncmp(*input, "|", 1)))
			input++;
		if (*input && !(ft_strncmp(*input, "|", 1)))
			arranged[++i] = get_redirect(input++);
		i++;
	}
	arranged[i] = NULL;
	return (arranged);
}
