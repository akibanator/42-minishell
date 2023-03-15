/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:12:30 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/14 14:10:57 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	main(int argc, char *argv[], char *envp[])
{
	// char		**input;
	// t_hell		*hell;
	// t_nelson	*nelson;
	int			i = 0;
	// int			j;

	// i = -1;
	if (argc > 1)
		ft_printf("%d%d\n", argv[1], envp[0]);
	while (i++ < 100000)
	{
		ft_printf("hello\n");
	}
	// // input = mini_split("echo   \"hello  42\" >outfile|ls libft objects sources |grep                    Mar|tr \"a A\"", ' ');
	// input = mini_split("grep banana >> eof", ' ');
	// hell = setup_hell(envp);
	// while (input[++i])
	// 	ft_printf("n%d-> [%s]\n", i + 1, input[i]);
	// hell->nelson = read_input(input, hell);
	// nelson = hell->nelson;
	// j = 1;
	// while (nelson)
	// {
	// 	i = 0;
	// 	ft_printf("n%d:", j);
	// 	while (nelson->content[i])
	// 		ft_printf("[%s]", nelson->content[i++]);
	// 	ft_printf("\n");
	// 	nelson = nelson->next;
	// 	j++;
	// }
	// hell->env = init_env(envp);
	// ft_free_nelson(hell->nelson);
	// free(hell->pwd);
	// free_env(hell->env);
	// close(hell->std_in);
	// close(hell->std_out);
	// ft_free_array(hell->path, (void *)hell->path);
	// free(hell);
}
