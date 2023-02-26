/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:50:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/02/26 12:25:56 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_doc(char *limiter)
{
	char	*here;
	char	*doc;

	here = NULL;
	doc = ft_strdup("");
	while (doc)
	{
		here = get_next_line(STDIN_FILENO);
		if (ft_strncmp(limiter, here, ft_strlen(limiter)))
		{
			doc = ft_strjoin_free(doc, here);
		}
		else
			break ;
		free(here);
	}
	free(here);
	return (doc);
}
