/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:51:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/14 13:50:04 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_input(char *input)
{
	while (*input != '\0')
	{
		if (*input != ' ')
			return (1);
		input++;
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_hell		*hell;
	char		*input;

	if (argc != 1 || argv[0][0] == 0)
	{
		ft_printf("invalid argument");
		exit(1);
	}
	hell = setup_hell(envp);
	hell->env = init_env(envp);
	hell->pwd = ft_strjoin(get_value("PWD", hell->env), "$ ");
	// while (1)
	// {
		input = readline(hell->pwd);
		// if (input == NULL)
		// 	break ;
		if (check_input(input))
			run_line(hell, read_input(edit_input(input, 1, 0)));
		free(input);
	// }
	free(hell->pwd);
	free_env(hell->env);
	close(hell->std_in);
	close(hell->std_out);
	ft_free_array(hell->path, (void *)hell->path);
	free(hell);
	return (0);
}
