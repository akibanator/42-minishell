/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:52:26 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/09 22:16:02 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>


typedef struct s_hell {
	int				std_in;
	int				std_out;
	int				exit_code;
	int				close;
	char			**path;
	struct s_env	*env;
	struct s_nelson	*nelson;
}	t_hell;

typedef struct s_env {
	char			*name_value;
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
void		run_redirect(t_hell *hell, t_nelson *node);
void		run_cmd(t_hell *hell, t_nelson *node);
void		run_builtin(t_hell *hell, t_nelson *node);
void		run_node(t_hell *hell, t_nelson *node);
void		run_line(t_hell *hell, t_nelson *node);

//setup
int			set_fds(t_hell *hell, t_nelson *node);
char		**get_path(char *envp[]);
t_env		*init_env(void);
t_hell		*setup_hell(char *envp[]);

//checks
int			ft_is_redirect(char *str);
int			ft_is_builtin(char	**str);
void		check_quotes(char *s);

//frees
void		ft_free_nelson(t_nelson *nelson);
void		free_env(t_env *env);

//read_input
char		**get_content(char *s);
char		*edit_input(char *input, int i, int j);
char		**mini_split(char const *s, char c);
t_nelson	*read_input(char *cmdline);

//builtins
int			ft_cd(char *str);
void		ft_pwd(void);
void		ft_env(t_env *env);
void		ft_echo(char **str);
void		ft_export(char *str, t_env *env);
t_env		*ft_unset(char *str, t_env *env);

//error
void	test(char *print, char *error, int flag);

#endif
