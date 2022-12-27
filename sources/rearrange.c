/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 04:08:37 by rarobert          #+#    #+#             */
/*   Updated: 2022/12/27 18:42:46 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	counter(char **input)
{
	int	i;

	i = 1;
	while (*input)
	{
		if (!(ft_strncmp(*input, "|")))
			i++;
		if (ft_isredirect(*input))
		{
			i++;
			input += 2;
		}
		input++;
	}
	return (i);
}

char	***rearrange_input(char **input)
{
	char	***arranged;
	int		i;

	i = 0;
	arranged = (char ***)malloc(sizeof(char **) * (counter(input) + 1));
	while (*input)
	{
		if (ft_isredirect(*input))
			arranged[i] = get_redirect(input);
		else
			arranged[i] = get_cmd(input);
		while (!ft_isredirect(*input) && (ft_stncmp(*inrput, "|")))
			input++;
		if (!(ft_strncmp(*input, "|")))
			input++;
		i++;
	}
	arranged[i] = NULL;
	return (arranged);
}
