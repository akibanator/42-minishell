/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:12:42 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/15 23:30:58 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *key, t_env *head)
{
	while (head)
	{
		if (!ft_strncmp(key, head->name, ft_strlen(key) + 1))
			return (head->value);
		head = head->next;
	}
	return ("");
}

char	*expand_variables(char *str, t_hell *hell)
{
	char	**line;
	char	*temp;

	if (!(have_var(str)))
		return (str);
	line = split_var(str);
	if (ft_strchr(line[2], '$'))
	{
		temp = line[2];
		line[2] = expand_variables(temp, hell);
		free(temp);
	}
	str = ft_strdup(line[0]);
	str = ft_strjoin_free(str, get_value(line[1] + 1, hell->env));
	str = ft_strjoin_free(str, line[2]);
	ft_free_array(line, (void *)line);
	return (str);
}

int	have_var(char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				str++;
			str++;
		}
		if (*str == '$')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

char	**split_var(char *str)
{
	char	**line;
	int		size;

	line = (char **)malloc(4 * sizeof(char *));
	line[0] = (char *)malloc(1 + get_size(str, 0) * sizeof(char));
	ft_strlcpy(line[0], str, get_size(str, 0) + 1);
	size = get_size(str, 0);
	line[1] = (char *)malloc(1 + get_size(str, 1) * sizeof(char));
	ft_strlcpy(line[1], &str[size], get_size(str, 1) + 1);
	size += get_size(str, 1);
	line[2] = (char *)malloc(1 + get_size(str, 2) * sizeof(char));
	ft_strlcpy(line[2], &str[size], get_size(str, 2) + 1);
	size += get_size(str, 2);
	line[3] = NULL;
	return (line);
}

int	get_size(char *str, int code)
{
	int	i;
	int	j;

	j = 1;
	i = -1;
	while (str[i + j] && str[++i] != '$')
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				;
			i++;
		}
	}
	if (code == 0)
		return (i);
	while (str[i + j] && str[i + j] != '$' && str[i + j] != ' ')
		j++;
	if (code == 1)
		return (j);
	i += j;
	j = 0;
	while (str[i + j])
		j++;
	return (j);
}
