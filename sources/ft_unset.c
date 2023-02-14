/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:19:43 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/14 11:29:17 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_unset(char *str, t_env *env)
{
	size_t	len_str;
	size_t	len_envname;
	t_env	*prev;
	t_env	*temp;

	prev = NULL;
	len_str = ft_strlen(str);
	while (ft_strncmp(env->name, "-EOF", 4) != 0)
	{
		len_envname = ft_strlen(env->name);
		if (!ft_strncmp(env->name, str, len_str) && len_str == len_envname)
		{
			if (prev != NULL)
			{
				temp = env->next;
				free(env->name);
				free(env->value);
				free(env);
				prev->next = temp;
			}
			else
			{
				temp = env;
				env = env->next;
				free(temp->name);
				free(temp->value);
				free(temp);
			}
		}
		prev = env;
		env = env->next;
	}
	return (env);
}
