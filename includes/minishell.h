/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:52:26 by rarobert          #+#    #+#             */
/*   Updated: 2022/12/30 04:35:33 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

typedef struct s_env {
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;


int		next_size(char *str);
char	**mini_split(char const *s, char c);
int		ft_is_builtin(char	**str);
t_env	*init_env();
void	free_env(t_env *env);
int		ft_cd(char *str);

#endif
