/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:51:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/15 00:12:39 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_hell *hell)
{
	t_env	*node;

	node = check_pwd(hell->env);
	if (hell->pwd)
		free(hell->pwd);
	hell->pwd = ft_strjoin(node->value, "$ ");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_hell		*hell;
	char		*input;

	input = NULL;
	check_args(argc, argv);
	hell = setup_hell(envp);
	while (1)
	{
		update_pwd(hell);
		sig_setup_prompt();
		free(input);
		input = readline(hell->pwd);
		if (input == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		if (check_input(&input, hell))
			run_line(hell, read_input(mini_split(input, ' '), hell), envp, -1);
		hell->lines++;
		update_exit_code(hell);
		ft_free_array(hell->path, (void *)hell->path);
		hell->path = get_path(hell->env);
	}
	ft_clear_all(hell);
}
