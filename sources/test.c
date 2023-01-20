/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:12:30 by rarobert          #+#    #+#             */
/*   Updated: 2023/01/19 22:04:18 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_hell {
	int				fd_in;
	int				fd_out;
	int				exit_code;
	char			**path;
	struct s_env	*start;
	struct s_nelson	*start;
}	t_hell;

char	**get_path(char *envp[]);


char	**get_path(char *envp[])
{
	size_t	i;
	char	*path_arr;

	i = -1;
	while (envp[++i])
		if (!(ft_strncmp("PATH", envp[i], 4)))
			path_arr = envp[i];
	return (ft_split(path_arr, ':'));
}

void	run_pipe(t_hell *hell, t_nelson *node)
{
	if (node->is_done == 2)
		return ;
	if (node->is_done == FALSE)
	{
		if (hell->fd_out != -2)
			close(hell->fd_out);
	}
	if (node->is_done == 1)
	{
		if (hell->fd_in != -2)
			close(hell->fd_in);
	}
}

void	run_redirect(t_hell *hell, t_nelson *node)
{
	if (node->is_done)
		return ;
	if (node->content[0][0] == '<')
	{
		if (hell->fd_in != -2)
			close(hell->fd_in);
		if ((node->content[0][0]) != node->content[0][1])
			hell->fd_in = open(node->content[1], O_RDONLY);
		else
			here_doc();
		dup2(hell->fd_in, STDIN_FILENO);
	}
	if (node->content[0][0] == '>')
	{
		if (hell->fd_out != -2)
			close(hell->fd_out);
		if ((node->content[0][0]) != node->content[0][1])
			hell->fd_out = open(node->content[1],
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			hell->fd_out = open(node->content[1],
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		dup2(hell->fd_out, STDOUT_FILENO);
	}
	node->is_done++;
}

void	run_cmd(t_hell *hell, t_nelson *node)
{

}

void	run_builtin(t_hell *hell, t_nelson *node)
{
	if (!ft_strncmp(str[0], "echo", 4))
		ft_echo(node->content);
	else if (!ft_strncmp(str[0], "cd", 2))
		ft_cd(node->content);
	else if (!ft_strncmp(str[0], "pwd", 3))
		ft_pwd(node->content);
	else if (!ft_strncmp(str[0], "export", 6))
		ft_export(node->content);
	else if (!ft_strncmp(str[0], "unset", 5))
		ft_unset(node->content);
	else if (!ft_strncmp(str[0], "env", 3))
		ft_env(node->content);
	else if (!ft_strncmp(str[0], "exit", 4))
		ft_exit();
}

void	run_node(t_hell *hell, t_nelson *node)
{
	
}

void	basic_setup(t_hell *hell, char *envp[])
{
	hell->path = get_path(envp);
	hell->fd_in = -2;
	hell->fd_out = -2;
	hell->std_in = dup(STDIN_FILENO);
	hell->std_out = dup(STDOUT_FILENO);
	hell->exit_code = 0;
}


int	main(void)
{
	t_nelson	*input_list;
	char		*test;
	int			i;
	int			j;

	test = ft_strdup("./minishell test test2|cmd|cmd2>hi");
	input_list = read_input(edit_input(test, -1, 0));
	j = 0;
	ft_printf("noedit input = %s\n", test);
	ft_printf("edited input = %s\n", edit_input(test, -1, 0));
	while (input_list)
	{
		i = -1;
		while (input_list->content[++i])
			ft_printf("content[%d][%d] = [%s]\n", j, i, input_list->content[i]);
		input_list = input_list->next;
		j++;
	}
}
