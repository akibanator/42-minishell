/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:51:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/02 21:24:29 by rarobert         ###   ########.fr       */
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
	if (argc != 1 || argv[0][0] == 0)
	{
		ft_printf("invalid argument");
		exit(1);
	}
	hell = setup_hell(envp);
	hell->env = init_env(envp);
	while (1)
	{
		update_pwd(hell);
		sig_setup_prompt();
		free(input);
		// dup2(hell->std_in, STDIN_FILENO);
		// dup2(hell->std_out, STDOUT_FILENO);
		input = readline(hell->pwd);
		if (input == NULL)
			break ;
		if (check_input(input))
		{
			run_line(hell, read_input(hell, edit_input(input, 1, 0)));
			// ft_printf("input = [%s]\nnumber of commands = %d", read_input(hell, edit_input(input, 1, 0)), hell->cmd_nbr);
			ft_printf("number of commands = %d\n", hell->cmd_nbr);
			add_history(input);
		}
	}
	rl_clear_history();
	free(hell->pwd);
	free_env(hell->env);
	close(hell->std_in);
	close(hell->std_out);
	ft_free_array(hell->path, (void *)hell->path);
	free(hell);
	return (0);
}
