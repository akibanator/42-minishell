/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:04:00 by akenji-a          #+#    #+#             */
/*   Updated: 2023/02/03 06:19:51 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exp_var	*init_struct(char *str)
{
	t_exp_var	*head;

	if (str)
		head = malloc(sizeof(t_exp_var));
	else
		return (NULL);
	return (head);
}

static size_t	gen_strlen(char const *str, char delim)
{
	size_t	i;

	i = 0;
	while (str[i] != delim && str[i])
		i++;
	return (i);
}

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

static t_exp_var	*split_bef(t_exp_var *node, char *old_str)
{
	size_t	len;

	len = gen_strlen(old_str, '$');
	node->str = ft_strndup(old_str, len);
	node->next = malloc(sizeof(t_exp_var));
	return (node->next);
}

static t_exp_var	*split_aft(t_exp_var *node, char *old_str)
{
	size_t	len;

	len = gen_strlen(old_str, ' ');
	node->str = ft_strndup(old_str, len);
	node->next = malloc(sizeof(t_exp_var));
	return (node->next);
}

static void	split_end(t_exp_var *node, char *old_str)
{
	size_t	len;

	len = gen_strlen(old_str, '\0');
	node->str = ft_strndup(old_str, len);
	node->next = malloc(sizeof(t_exp_var));
	node->next->str = ft_strdup(" ");
}

static char	*skip_spaces(char *str)
{
	while (*str != ' ' && *str != '\0')
		str++;
	return (str);
}

static t_env	*find_exp_var(char	*str, t_env *env)
{
	while (ft_strncmp(env->name, "-EOF", 4) != 0)
	{
		if (ft_strcmp(str, env->name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static void	replace_exp_var(t_exp_var *node, t_env *env)
{
	t_env	*head;
	t_env	*temp;
	char	*str;

	head = env;
	while (ft_strncmp(node->str, " ", 1) != 0)
	{
		env = head;
		if (ft_strncmp(node->str, "$", 1) == 0)
		{
			str = node->str;
			temp = find_exp_var(++str, env);
			if (temp != NULL)
			{
				free(node->str);
				node->str = ft_strdup(temp->value);
			}
			else
			{
				free(node->str);
				node->str = ft_strdup("");
			}
		}
		node = node->next;
	}
}

static char	*join_nodes(t_exp_var *node)
{
	char	*new_str;
	char	*temp;

	temp = node->str;
	new_str = ft_strdup(node->str);
	node = node->next;
	free(temp);
	while (ft_strncmp(node->str, " ", 1) != 0)
	{
		temp = node->str;
		new_str = ft_strjoin(new_str, node->str);
		node = node->next;
		free(temp);
	}
	temp = node->str;
	new_str = ft_strjoin(new_str, node->str);
	node = node->next;
	free(temp);
	return (new_str);
}

static t_exp_var	*call_split(t_exp_var *node, char *old_str, char *str)
{
	node = split_bef(node, old_str);
	node = split_aft(node, str);
	return (node);
}

char	*exp_var(char *str, t_env *env)
{
	int			quote;
	char		*old_str;
	t_exp_var	*head;
	t_exp_var	*current;

	check_quotes(str);
	quote = -1;
	old_str = str;
	head = init_struct(str);
	current = head;
	while (*str != '\0' && head != NULL)
	{
		if (*str == '\'')
			quote *= -1;
		if (*str == '$' && quote == -1)
		{
			current = call_split(current, old_str, str);
			str = skip_spaces(str);
			old_str = str;
		}
		str++;
	}
	split_end(current, old_str);
	replace_exp_var(head, env);
	return (join_nodes(head));
}
