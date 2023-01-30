/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:12:30 by rarobert          #+#    #+#             */
/*   Updated: 2023/01/29 21:08:26 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static char	*get_cmd(t_hell *hell, t_nelson *node)
{
	size_t	j;
	char	*cmd;

	if (node->content[0][0] == '.' && node->content[0][0] == '/')
		return (node->content[0]);
	j = 0;
	cmd = ft_strdup(node->content[0]);
	while (hell->path[++j])
	{
		free(node->content[0]);
		node->content[0] = ft_strjoin(hell->path[j], "/");
		node->content[0] = ft_strjoin_free(node->content[0], cmd);
		if (access(node->content[0], 0) == 0)
		{
			free(cmd);
			hell->exit_code = 0;
			return (node->content[0]);
		}
	}
	free (node->content[0]);
	// cmd_error(cmd);
	hell->exit_code = 127;
	return (cmd);
}

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
	if (node->is_done == 0)
	{
		dup2(node->pipe[1], STDOUT_FILENO);
		close(node->pipe[1]);
	}
	if (node->is_done == 1)
	{
		dup2(node->pipe[0], STDIN_FILENO);
		close(STDOUT_FILENO);
		dup(hell->std_out);
		hell->std_out = dup(STDOUT_FILENO);
		close(node->pipe[0]);
	}
	node->is_done++;
}

void	run_redirect(t_hell *hell, t_nelson *node)
{
	if (node->is_done)
		return ;
	if (node->content[0][0] == '<')
	{
		if (hell->std_in != -2)
			close(hell->std_in);
		if ((node->content[0][0]) != node->content[0][1])
			hell->std_in = open(node->content[1], O_RDONLY);
		else
			ft_printf("here_doc");
		dup2(hell->std_in, STDIN_FILENO);
	}
	if (node->content[0][0] == '>')
	{
		if (hell->std_out != -2)
			close(hell->std_out);
		if ((node->content[0][0]) != node->content[0][1])
			hell->std_out = open(node->content[1],
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			hell->std_out = open(node->content[1],
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		dup2(hell->std_out, STDOUT_FILENO);
	}
	node->is_done++;
}

void	run_cmd(t_hell *hell, t_nelson *node)
{
	pid_t	child;

	node->content[0] = get_cmd(hell, node);
	child = fork();
	if (child == 0)
	{
		execve(node->content[0], node->content, 0);
		exit(1);
	}
}

void	run_builtin(t_hell *hell, t_nelson *node)
{
	pid_t	child;
	
	child = fork();
	if (child == 0)
	{
		if (!ft_strncmp(node->content[0], "echo", 4))
			ft_echo(node->content);
	// 	else if (!ft_strncmp(node->content[0], "pwd", 3))
	// 		ft_pwd(node->content);
	// 	else if (!ft_strncmp(node->content[0], "env", 3))
	// 		ft_env(node->content);
	}
	// if (!ft_strncmp(node->content[0], "cd", 2))
	// 	ft_cd(node->content[0]);
	else if (!ft_strncmp(node->content[0], "export", 6))
		ft_export(node->content[0], hell->env);
	// else if (!ft_strncmp(node->content[0], "unset", 5))
	// 	ft_unset(node->content[0], hell->env);
	// else if (!ft_strncmp(node->content[0], "exit", 4))
	// 	ft_exit();
}

void	run_node(t_hell *hell, t_nelson *node)
{
	if (node->content[0][0] == '|')
		run_pipe(hell, node);
	else if (ft_is_redirect(node->content[0]))
		run_redirect(hell, node);
	else
	{
		hell->close = set_fds(hell, node);
		if (ft_is_builtin(node->content))
			run_builtin(hell, node);
		else
			run_cmd(hell, node);
	}
}

void	ft_free_array(char **array, void *aux)
{
	while (*array)
		free(*array++);
	free(aux);
}

int	set_fds(t_hell *hell, t_nelson *node)
{
	while(node)
	{
		if (node->content[0][0] == '|')
		{
			run_pipe(hell, node);
			return (node->pipe[0]);
		}
		if (ft_is_redirect(node->content[0]))
			run_redirect(hell, node);
		node = node->next;
	}
	return (-2);
}

t_hell	*setup_hell(char *envp[])
{
	t_hell	*hell;

	hell = (t_hell *)malloc(sizeof(t_hell));
	hell->path = get_path(envp);
	hell->std_in = dup(STDIN_FILENO);
	hell->std_out = dup(STDOUT_FILENO);
	hell->exit_code = 0;
	return (hell);
}

void	ft_free_nelson(t_nelson *nelson)
{
	t_nelson	*aux;

	while (nelson)
	{
		ft_free_array(nelson->content, (void *)nelson->content);
		aux = nelson;
		nelson = nelson->next;
		free(aux);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_nelson	*input_list;
	t_nelson	*start;
	t_hell		*hell;
	char		*input;
	// int			i;
	// int			j;

	if (argc == 1)
		ft_printf("running %s\n", argv[0]);
	input_list = read_input(edit_input(argv[1], -1, -1));
	start = input_list;
	input = edit_input(argv[1], -1, -1);
	ft_printf("noedit input = %s\n", argv[1]);
	ft_printf("edited input = %s\n", input);
	free(input);
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
	run_node(hell, start);
	run_node(hell, start->next);
	run_node(hell, start->next->next);
	run_node(hell, start->next->next->next);
	run_node(hell, start->next->next->next->next);
	ft_free_array(hell->path, (void *)hell->path);
	ft_free_nelson(start);
	// close(19);
	// close(23);
	close(hell->std_in);
	close(hell->std_out);
	free(hell);
}
