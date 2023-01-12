/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:52:26 by rarobert          #+#    #+#             */
/*   Updated: 2023/01/12 01:29:01 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

typedef struct s_nelson {
	int				pipe[2];
	int				is_done;
	char			**content;
	struct s_nelson	*next;
}					t_nelson;

void		check_quotes(char *s);
int			ft_is_redirect(char *str);
char		**get_content(char *s);
char		*edit_input(char *input, int i, int j);
t_nelson	*read_input(char *cmdline);
char		**mini_split(char const *s, char c);

#endif