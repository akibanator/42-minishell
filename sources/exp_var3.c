/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:04:00 by akenji-a          #+#    #+#             */
/*   Updated: 2023/01/30 13:01:12 by akenji-a         ###   ########.fr       */
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

static char			*before_dol(t_exp_var *exp, char *str)
{

}

char	*exp_var(char *str, t_env *env)
{
	int			quote;
	size_t		i;
	char		*temp;
	t_exp_var	*head;
	t_exp_var	*current;

	i = 0;
	quote = -1;
	temp = str;
	head = init_struct(str);
	current = head;
	while (*str != '\0' && head != NULL)
	{
		if (*str == '\'')
			quote *= -1;
		if (*str == '$' && quote == -1)
		{
			temp = before_dol(current, str);
		}
		ft_printf("%c", *str);
		str++;
	}
	ft_printf("\n");
	ft_printf("%s", temp);
	ft_printf("\n");
}
