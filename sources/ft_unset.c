/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:19:43 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/02 23:37:16 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*unset_first_node(t_env *head)
{
	t_env	*temp;

	temp = head->next;
	free(head->name);
	free(head->value);
	free(head);
	return (temp);
}

static void	unset_node(t_env *next_env, t_env *env)
{
	t_env	*temp;

	temp = next_env->next;
	free(next_env->name);
	free(next_env->value);
	free(next_env);
	env->next = temp;
}

t_env	*ft_unset(char *str, t_env *env)
{
	t_env	*head;

	head = env;
	if (str == NULL)
		return (head);
	if (!ft_strcmp(env->name, str))
		return (unset_first_node(env));
	env = env->next;
	while (env)
	{
		if (env->next)
		{
			if (!ft_strcmp(env->next->name, str))
			{
				unset_node(env->next, env);
				break ;
			}
		}
		env = env->next;
	}
	return (head);
}
