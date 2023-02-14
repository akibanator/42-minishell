/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:12:30 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/14 02:10:51 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

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

static char *check_pwd(t_hell *hell)
{
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_hell		*hell;
	char		*input;
	char		*curr_dir;

	if (argc != 1)
	{
		ft_printf("invalid argument %s\n", argv[0]);
		exit(1);
	}
	else
		ft_printf("running %s\n", argv[0]);
	hell = setup_hell(envp);
	hell->env = init_env(envp);
	while (1)
	{
		curr_dir =  check_pwd(hell);
		input = readline(curr_dir);
		if (input == NULL)
			break ;
		if (check_input(input))
			run_line(hell, read_input(edit_input(input, 1, 0)));
		free(input);
	}
	free_env(hell->env);
	close(hell->std_in);
	close(hell->std_out);
	ft_free_array(hell->path, (void *)hell->path);
	free(hell);
}
