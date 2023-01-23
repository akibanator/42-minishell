/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:04:00 by akenji-a          #+#    #+#             */
/*   Updated: 2023/01/19 13:25:21 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;

	s2 = (char *)malloc(n + 1);
	if (!s2)
		return (0);
	ft_memcpy(s2, s1, n);
	s2[n + 1] = 0;
	return (s2);
}

static t_exp_var	*init_struct(char *str)
{
	t_exp_var	*head;

	if (str)
		head = malloc(sizeof(t_exp_var));
	else
		return (NULL);
	return (head);
}

static size_t	split_exp_var(size_t lst_i, size_t i, char *str, t_exp_var *ev)
{
	char	*new_str;

	new_str = ft_strndup(&str[lst_i], i - lst_i);
	ev->str = new_str;
	ev->next = malloc(sizeof(t_exp_var));
	if (ev->next == NULL)
		exit(1);
	lst_i = i;
	return (lst_i);
}

static char	*find_env(char *str, t_env *env)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	while (ft_strncmp(env->name, "-EOF", 4) != 0)
	{
		if (ft_strcmp(env->name, str) == 0)
		{
			new_str = ft_strdup(env->value);
			return (new_str);
		}
		env = env->next;
	}
	new_str = ft_strdup("");
	return (new_str);
}

static size_t	split_dol(size_t lst_i, size_t i, char *str, t_exp_var *ev, t_env *env)
{
	size_t	len;
	size_t	i_temp;
	char	*new_str;
	char	*ret_env;

	len = 0;
	i_temp = i + 1;
	while (str[i] != '\0' && str[i] != ' ')
	{
		i++;
		len++;
	}
	new_str = ft_strndup(&str[i_temp], len - 1);
	ret_env = find_env(new_str, env);
	ev->str = ret_env;
	ev->next = malloc(sizeof(t_exp_var));
	if (ev->next == NULL)
		exit(1);
	return (lst_i + i);
}

char	*exp_var(char *str, t_env *env)
{
	size_t		i;
	size_t		last_i;
	t_exp_var	*head;
	t_exp_var	*current;
	int			quote_state;

	i = 0;
	last_i = i;
	head = init_struct(str);
	current = head;
	quote_state = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			quote_state *= -1;
		if (str[i + 1] == '\0' || str[i] == '$')
		{
			last_i = split_exp_var(last_i, i, str, current);
			current = current->next;
		}
		if (str[i] == '$' && quote_state == 1)
		{
			last_i = split_dol(last_i, i, str, current, env);
			current = current->next;
			i = last_i;
		}
		i++;
	}
}
