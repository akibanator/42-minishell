/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:19:17 by akenji-a          #+#    #+#             */
/*   Updated: 2023/01/13 08:26:11 by akenji-a         ###   ########.fr       */
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

static void	single_quote(char *str, t_exp_var *node)
{
	size_t	len;
	char	*node_str;

	len = 1;
	while (str[len] != '\'' && str[len] != '\0')
		len++;
	len++;
	node_str = malloc((len + 1) * sizeof(char));
	node_str[len] = '\0';
	while (len--)
		node_str[len] = str[len];
	node->str = node_str;
}

char	*exp_var(char *str)
{
	t_exp_var	*current;
	t_exp_var	*head;

	check_quotes(str);
	head = init_struct(str);
	current = head;
	while (*str && head != NULL)
	{
		if (*str == '\'' && *(str + 1) != '\0')
		{
			single_quote(str, current);
		}
		str++;
	}
	free(head->str);
	free(head);
	return (str);
}
