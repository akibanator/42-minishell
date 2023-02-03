/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:51:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/03 06:11:20 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_env	*env;

	env = init_env();

	char	*str;
	char	*ret_str;
	str = ft_strdup("ahuah $USER 'ahu $ahuhau'");
	ret_str = exp_var(str, env);
	ft_printf("%s\n", ret_str);
	free(str);
	free(ret_str);
	str = ft_strdup("dfasuias'fdh $usdfahui'");
	ret_str = exp_var(str, env);
	ft_printf("%s\n", ret_str);
	free(str);
	free(ret_str);
	str = ft_strdup("dfasuias $SHELL 'fdh $usdfahui'");
	ret_str = exp_var(str, env);
	ft_printf("%s\n", ret_str);
	free(str);
	free(ret_str);
	str = ft_strdup("dfas$fahui dfsaujisfdhuus");
	ret_str = exp_var(str, env);
	ft_printf("%s\n", ret_str);
	free(str);
	free(ret_str);
	free_env(env);
	return (0);
}
