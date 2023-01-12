/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:14:26 by akenji-a          #+#    #+#             */
/*   Updated: 2023/01/12 15:25:22 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

static size_t	gen_strlen(char const *str, char delim)
{
	size_t	i;

	i = 0;
	while (str[i] != delim && str[i])
		i++;
	return (i + 1);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (ft_strncmp(env->name, "-EOF", 4) != 0)
	{
		temp = env->next;
		free(env->name_value);
		free(env->name);
		free(env->value);
		free(env);
		env = temp;
	}
	free(env->name);
	free(env);
}

static t_env	*init_struct(char **str)
{
	t_env	*head;

	if (*str)
		head = malloc(sizeof(t_env));
	else
		return (NULL);
	return (head);
}

t_env	*init_env(void)
{
	char	**str;
	t_env	*head;
	t_env	*current;
	char	*pos_chr;

	str = environ;
	head = init_struct(str);
	current = head;
	while (*str && head != NULL)
	{
		current->name_value = ft_strdup(*str);
		pos_chr = ft_strchr(*str, '=');
		current->value = ft_strdup(++pos_chr);
		current->name = malloc(gen_strlen(*str, '=') * sizeof(char));
		ft_strlcpy(current->name, *str, gen_strlen(*str, '='));
		str++;
		current->next = malloc(sizeof(t_env));
		current = current->next;
	}
	current->name = ft_strdup("-EOF");
	return (head);
}
