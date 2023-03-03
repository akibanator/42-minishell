/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:14:26 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/03 00:53:06 by akenji-a         ###   ########.fr       */
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

	while (env)
	{
		temp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = temp;
	}
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j] != '\0')
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_workspace_vars(char *var)
{
	if (ft_strstr(var, "WORKSPACE_HTTP_PORT"))
		return (1);
	if (ft_strstr(var, "WORKSPACE_HTTP_SERVICE"))
		return (1);
	if (ft_strstr(var, "WORKSPACE_SSH_PORT"))
		return (1);
	if (ft_strstr(var, "WORKSPACE_SSH_SERVICE"))
		return (1);
	if (ft_strstr(var, "WORKSPACE_VNC_PORT"))
		return (1);
	if (ft_strstr(var, "WORKSPACE_VNC_SERVICE"))
		return (1);
	return (0);
}

t_env	*init_env(char *envp[])
{
	t_env	*head;
	t_env	*current;
	char	*pos_chr;

	head = malloc(sizeof(t_env));
	current = head;
	while (*envp)
	{
		while (check_workspace_vars(*envp) && *(envp + 1) != NULL)
			envp++;
		pos_chr = ft_strchr(*envp, '=');
		current->value = ft_strdup(++pos_chr);
		current->name = malloc(gen_strlen(*envp, '=') * sizeof(char));
		ft_strlcpy(current->name, *envp, gen_strlen(*envp, '='));
		envp++;
		if (*envp)
		{
			current->next = malloc(sizeof(t_env));
			current = current->next;
		}
	}
	current->next = NULL;
	return (head);
}
