/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:50:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/14 00:42:41 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_here_doc(char *limiter, char **here)
{
	char	*doc;

	doc = ft_strdup("");
	sig_setup_heredoc();
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

int	here_doc(char *limiter, t_hell *hell)
{
	char	*here;
	char	*doc;
	int		fd;
	int		temp;

	here = NULL;
	doc = read_here_doc(limiter, &here);
	fd = open("temp_file", O_CREAT | O_WRONLY, 0644);
	temp = open("fd_checker", O_CREAT | O_WRONLY, 0644);
	write(fd, doc, ft_strlen(doc));
	free(doc);
	fd = open("temp_file", O_RDONLY);
	dup2(hell->std_in, STDIN_FILENO);
	dup2(hell->std_err, STDERR_FILENO);
	unlink ("temp_file");
	unlink ("fd_checker");
	sig_setup_prompt();
	if (here && !ft_strncmp(limiter, here, ft_strlen(limiter)))
	{
		free(here);
		return (fd);
	}
	else if (temp == 2)
		ft_printf("control C");
	else
		ft_printf("control D");
	write(2, "\n", 1);
	return (fd);
}
