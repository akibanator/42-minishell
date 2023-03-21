/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:50:43 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/21 00:16:47 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(char **str, int flag_n, int count)
{
	int		i;
	char	c;

	while (count--)
		str++;
	while (*str)
	{
		i = 0;
		while (*(*str + i) != '\0')
		{
			c = *(*str + i);
			write(1, &c, 1);
			i++;
		}
		str++;
		if (*str)
			write(1, " ", 1);
	}
	if (!flag_n)
		write(1, "\n", 1);
}

void	ft_echo(char **str)
{
	int	flag_n;
	int	i;

	ft_printf("str1= [%s]\n", str[1]);
	ft_printf("str2= [%s]\n", str[2]);
	ft_printf("str3= [%s]\n", str[3]);
	flag_n = 0;
	i = 1;
	if (str[i] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	if ((ft_strcmp(str[i], "-n") == 0))
	{
		while ((ft_strcmp(str[i], "-n") == 0) && (str[i + 1] != NULL))
			i++;
		flag_n = 1;
	}
	if (flag_n == 0)
		print_echo(str, 0, 1);
	else
		print_echo(str, 1, i);
}
