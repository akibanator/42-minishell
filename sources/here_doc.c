/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:50:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/26 12:36:12 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_doc(char *limiter)
{
	char	*here;
	char	*doc;

	doc = ft_strdup("");
	here = get_next_line(STDIN_FILENO);
	while (ft_strncmp(limiter, here, ft_strlen(limiter)))
	{
		if (ft_strncmp(limiter, here, ft_strlen(limiter)))
			doc = ft_strjoin_free(doc, here);
		free(here);
		here = get_next_line(STDIN_FILENO);
	}
	free(here);
	return (doc);
}
