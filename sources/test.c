/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:12:30 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/09 23:02:37 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_hell		*hell;
	// int			i;
	// int			j;    

	if (argc == 1)
		ft_printf("running %s\n", argv[0]);
	// input = edit_input(argv[1], 1, -1);
	// ft_printf("noedit input = %s\n", argv[1]);
	// ft_printf("edited input = %s\n", input);
	// free(input);
	// j = 0;
	// while (input_list)
	// {
	// 	i = -1;
	// 	while (input_list->content[++i])
	// 		ft_printf("content[%d][%d] = [%s]\n", j, i, input_list->content[i]);
	// 	input_list = input_list->next;
	// 	j++;
	// }
	hell = setup_hell(envp);
	hell->env = init_env(envp);
	run_line(hell, read_input(edit_input(argv[1], 1, -1)));
	// close(19);
	// close(23);
	free_env(hell->env);
	close(hell->std_in);
	close(hell->std_out);
	ft_free_array(hell->path, (void *)hell->path);
	free(hell);
}
