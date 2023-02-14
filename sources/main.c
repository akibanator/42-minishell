/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:51:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/14 11:25:05 by akenji-a         ###   ########.fr       */
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

	if (argc == 1)
		ft_printf("running %s\n", argv[0]);
	else
	{
		ft_printf("invalid argument");
		exit(1);
	}
	hell = setup_hell(envp);
	hell->env = init_env(envp);
	// while (1)
	// {
		input = readline("minishell: ");
		// if (input == NULL)
			// break ;
		if (check_input(input))
			run_line(hell, read_input(edit_input(input, 1, 0)));
		free(input);
	// }
	free_env(hell->env);
	close(hell->std_in);
	close(hell->std_out);
	ft_free_array(hell->path, (void *)hell->path);
	free(hell);
	return (0);
}
