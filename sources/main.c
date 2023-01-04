/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:51:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/01/04 08:11:55 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	**str4;

	str1 = ft_strdup("echo");
	str2 = ft_strdup("-n");
	str3 = ft_strdup("ehauehauheauaehuh\naehuheauhae\neahuehaeuh");
	str4 = malloc(3 * sizeof(char *));
	str4[0] = str1;
	str4[1] = str2;
	str4[2] = str3;
	ft_echo(str4);
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	str1 = ft_strdup("echo");
	str2 = ft_strdup("aaaaaaaaaaaafdisuahfiasudhfds\naaaaaaaaaa\n aaaaaaaaaaaaaaa");
	str4 = malloc(2 * sizeof(char *));
	str4[0] = str1;
	str4[1] = str2;
	ft_echo(str4);
	free(str1);
	free(str2);
	free(str4);
	return (0);
}
