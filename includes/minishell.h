/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:52:26 by rarobert          #+#    #+#             */
/*   Updated: 2022/12/30 22:14:49 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

typedef struct s_nelson {
	int				pipe[2];
	int				is_done;
	int				is_dq;
	char			**cmd;
	struct t_nelson	*next;
}					t_nelson;

void	check_quotes(char *s);
int		ft_is_redirect(char *str);
char	**mini_split(char const *s, char c);

#endif