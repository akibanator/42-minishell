/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:14:26 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/14 11:29:18 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_env	*init_env(char *envp[])
{
	t_env	*head;
	t_env	*current;
	char	*pos_chr;

	head = init_struct(envp);
	current = head;
	while (*envp && head != NULL)
	{
		pos_chr = ft_strchr(*envp, '=');
		current->value = ft_strdup(++pos_chr);
		current->name = malloc(gen_strlen(*envp, '=') * sizeof(char));
		ft_strlcpy(current->name, *envp, gen_strlen(*envp, '='));
		envp++;
		current->next = malloc(sizeof(t_env));
		current = current->next;
	}
	current->name = ft_strdup("-EOF");
	current->next = NULL;
	return (head);
}
