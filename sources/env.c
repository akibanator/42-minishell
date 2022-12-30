/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:14:26 by akenji-a          #+#    #+#             */
/*   Updated: 2022/12/30 04:26:16 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

static void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (ft_strncmp(env->name, "-EOF", 4) != 0)
	{
		temp = env->next;
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
	char	**split;

	str = environ;
	head = init_struct(str);
	current = head;
	while (*str && head != NULL)
	{
		split = ft_split(*str, '=');
		current->name = ft_strdup(split[0]);
		if (split[1] != NULL)
			current->value = ft_strdup(split[1]);
		else
			current->value = ft_strdup("");
		free_split(split);
		str++;
		current->next = malloc(sizeof(t_env));
		current = current->next;
	}
	current->name = ft_strdup("-EOF");
	return (head);
}
