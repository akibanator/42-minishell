/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:51:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/01/17 22:31:52 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_env	*env;

	env = init_env();

	char	*str;
	char	*ret_str;
	str = ft_strdup("echo \'\"$sfhau $asdfTE\"\'ahsd $TERM_PROGRAM ");
	ret_str = exp_var(str, env);
//	ft_printf("%s\n", ret_str);
	free(str);
	free_env(env);
	return (0);
}
