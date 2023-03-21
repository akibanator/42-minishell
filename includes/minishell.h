/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:52:26 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/21 04:58:13 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_hell {
	int				std_in;
	int				std_out;
	int				std_err;
	int				exit_code;
	int				here_code;
	int				cmd_nbr;
	int				to_close;
	int				lines;
	pid_t			*pids;
	char			*pwd;
	char			**path;
	struct s_env	*env;
	struct s_nelson	*nelson;
}	t_hell;

typedef struct s_env {
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_nelson {
	int				pipe[2];
	int				is_done;
	char			**content;
	struct s_nelson	*next;
}	t_nelson;

//run
void		run_pipe(t_hell *hell, t_nelson *node);
void		run_redirect(t_nelson *node, t_hell *hell);
void		run_cmd(t_hell *hell, t_nelson *node, char *envp[]);
void		run_builtin(t_hell *hell, t_nelson *node);
void		run_node(t_hell *hell, t_nelson *node, char *envp[]);
void		run_line(t_hell *hell, t_nelson *node, char *envp[], int i);
void		update_exit_code(t_hell *hell);

//setup
void		set_fds(t_hell *hell, t_nelson *node);
char		**get_path(t_env *env);
t_env		*init_env(char *envp[]);
t_hell		*setup_hell(char *envp[]);

//checks
t_env		*check_pwd(t_env *head);
int			check_input(char *input);
int			ft_is_redirect(const char *str);
int			ft_is_builtin(const char	*str);
void		check_args(int argc, char *argv[]);
char		*check_quotes(char *s, t_hell *hell);

//var_expansion
int			get_size(char *str, int code);
char		*get_value(char *key, t_env *head);
char		**split_var(char *str);
char		*expand_variables(char *str, t_hell *hell);

//read_input
char		**split_nelson(char *s, char c);
int			here_doc(char *limiter, t_hell *hell);
t_nelson	*get_node(char **s, t_hell *hell);
t_nelson	*read_input(char *cmdline, t_hell *hell);

//builtins
void		ft_env(t_env *env);
void		ft_echo(char **str);
void		ft_pwd(t_env *head);
void		export_no_args(t_env *head);
int			ft_cd(char *str, t_env *head);
void		ft_export(char *str, t_env *env);
void		ft_exit(t_hell *hell, char **args, t_nelson *node);
t_env		*ft_unset(char *str, t_env *env);

//error
void		cmd_error(char *print, char *error, int flag);

//signals
void		sig_int_handle(int signal);
void		sig_setup_exec(pid_t id);
void		sig_setup_prompt(void);
void		sig_setup_heredoc(void);
void		sig_int_handle_heredoc(int signal);
void		sig_quit_handle_heredoc(int signal);

//memory
void		clear_fd(void);
void		free_env(t_env *env);
void		ft_clear_all(t_hell *hell);
void		ft_free_nelson(t_nelson *nelson);

#endif
