/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:12:30 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/05 18:50:55 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	**input;
	int		i;

	i = -1;
	input = mini_split("echo   \"hello  42\" >outfile| ls -l |grep                    Mar|tr \"a A\"", ' ');
	while (input[++i])
		ft_printf("n%d-> [%s]\n", i + 1, input[i]);
	ft_free_array(input, (void *)input);
}
