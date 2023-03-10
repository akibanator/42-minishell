/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:50:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/08 17:12:49 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static char *read_here_doc(char *limiter, char **here)
{
	char	*doc;

	doc = ft_strdup("");
	*here = get_next_line(STDIN_FILENO);
	while (*here && ft_strncmp(limiter, *here, ft_strlen(limiter)))
	{
		if (ft_strncmp(limiter, *here, ft_strlen(limiter)))
			doc = ft_strjoin_free(doc, *here);
		free(*here);
		*here = get_next_line(STDIN_FILENO);
	}
	return (doc);
}

int	here_doc(char *limiter)
{
	char	*here;
	char	*doc;
	int		fd;
	int		temp;

	here = NULL;
	doc = read_here_doc(limiter, &here);
	fd = open("temp_file", O_CREAT | O_WRONLY, 0644);
	temp = open("fd_checker", O_CREAT | O_WRONLY, 0644);
	if (!ft_strncmp(limiter, here, ft_strlen(limiter)))
	{
		write(fd, doc, ft_strlen(doc));
		free(here);
		close (fd);
		fd = open("temp_file", O_RDONLY);
	}
	else if (temp == 1)
		ft_printf("control D");
	else if (temp != 0)
		ft_printf("control C");
	unlink ("temp_file");
	unlink ("fd_checker");
	// free(doc);
	return (fd);
}
