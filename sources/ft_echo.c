/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:50:43 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/15 00:45:43 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_remove_new_line(char *str)
{
	size_t	i;
	size_t	len_str;
	char	*initial_str;
	char	*new_str;

	i = 0;
	initial_str = str;
	while (*str != '\0')
	{
		if (*str == '\n')
			i++;
		str++;
	}
	str = initial_str;
	len_str = ft_strlen(str);
	new_str = malloc((len_str - i) + 1 * sizeof(char));
	initial_str = new_str;
	while (*str != '\0')
	{
		while (*str == '\n')
			str++;
		*new_str++ = *str++;
	}
	*new_str = '\0';
	return (initial_str);
}

void	ft_echo(char **str)
{
	char	*new_str;

	if (!ft_strncmp("-n", str[1], 2))
	{
		new_str = ft_remove_new_line(str[2]);
		ft_printf("%s", new_str);
		free(new_str);
	}
	else
	{
		while(*++str)
			ft_printf("%s ", *str);
		ft_printf("\n");
	}
}
