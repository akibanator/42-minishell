/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:51:53 by rarobert          #+#    #+#             */
/*   Updated: 2022/12/30 04:12:20 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	while (ft_strncmp(env->name, "-EOF", 4) != 0)
	{
		ft_printf("env->name: %s\n", env->name);
		if (env->value != NULL)
			ft_printf("env->value: %s\n", env->value);
		env = env->next;
	}
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

int	main(void)
{
	t_env	*env;

	env = init_env();
	print_env(env);
	free_env(env);
	return (0);
}
