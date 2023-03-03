/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:50:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/01 20:50:05 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_doc(char *limiter)
{
	char	*here;
	char	*doc;

	doc = ft_strdup("");
	here = readline("> ");
	if (here == NULL)
		return (doc);
	while (ft_strncmp(limiter, here, ft_strlen(limiter)))
	{
		doc = ft_strjoin_free(doc, here);
		free(here);
		here = readline("> ");
		if (here == NULL)
			break ;
	}
	free(here);
	// solucao alternativa, retornar em um arquivo temporario e depois unlink para remover o arquivo
	return (doc);
}
