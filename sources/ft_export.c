/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:19:17 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/14 11:29:48 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_export(char *str)
{
	while (*str != '\0')
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

static size_t	gen_strlen(char const *str, char delim)
{
	size_t	i;

	i = 0;
	while (str[i] != delim && str[i])
		i++;
	return (i + 1);
}

static int	find_env(char *name, char *value, t_env *env)
{
	size_t	len;

	len = ft_strlen(name);
	while (ft_strncmp(env->name, "-EOF", 4) != 0)
	{
		if (ft_strncmp(env->name, name, len) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

static void	create_env(char *name, char *value, t_env *env)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	new_env->next = env->next;
	env->next = new_env;
}

void	ft_export(char *str, t_env *env)
{
	char	*pos_chr;
	char	*value;
	char	*name;
	size_t	len;

	if (!is_valid_export(str))
		return ;
	pos_chr = ft_strchr(str, '=');
	value = ft_strdup(++pos_chr);
	len = gen_strlen(str, '=');
	name = malloc(len * sizeof(char));
	ft_strlcpy(name, str, len);
	if (!find_env(name, value, env))
		create_env(name, value, env);
	free(name);
	free(value);
}
