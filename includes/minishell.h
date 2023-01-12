/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:52:26 by rarobert          #+#    #+#             */
/*   Updated: 2023/01/12 05:28:47 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

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

void		check_quotes(char *s);
int			ft_is_redirect(char *str);
char		**get_content(char *s);
char		*edit_input(char *input, int i, int j);
t_nelson	*read_input(char *cmdline);
char		**mini_split(char const *s, char c);
int			ft_is_builtin(char	**str);
t_env		*init_env(void);
void		free_env(t_env *env);
int			ft_cd(char *str);
void		ft_env(t_env *env);
void		ft_echo(char **str);
void		ft_unset(char *str, t_env *env);

#endif
