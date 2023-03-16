/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:50:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/16 01:01:42 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_here_doc(char *limiter, char **here, t_hell *hell)
{
	char	*doc;

	doc = ft_strdup("");
	sig_setup_heredoc();
	write(2, "> ", 2);
	dup2(hell->std_in, STDIN_FILENO);
	*here = get_next_line(STDIN_FILENO);
	while (*here && ft_strncmp(limiter, *here, ft_strlen(limiter)))
	{
		write(2, "> ", 2);
		if (ft_strncmp(limiter, *here, ft_strlen(limiter)))
			doc = ft_strjoin_free(doc, *here);
		free(*here);
		*here = get_next_line(STDIN_FILENO);
	}
	return (doc);
}

static int	free_c(t_hell *hell)
{
	hell->here_code = 1;
	ft_printf("\n");
	return (-2);
}

static void	free_d(t_hell *hell, int fd)
{
	char	*str;
	char	*line;

	if (fd >= 0)
		close(fd);
	str = ft_strdup("warning: here-document at line ");
	line = ft_itoa(hell->lines);
	str = ft_strjoin_free(str, line);
	cmd_error("", str, 1);
	free(str);
	free(line);
}

static int	doc_nelson(char **here, int temp, int fd)
{
	free(*here);
	close(temp);
	return (fd);
}

int	here_doc(char *limiter, t_hell *hell)
{
	char	*here;
	char	*doc;
	int		fd;
	int		temp;

	here = NULL;
	doc = read_here_doc(limiter, &here, hell);
	fd = open("temp_file", O_CREAT | O_WRONLY, 0644);
	temp = open("fd_checker", O_CREAT | O_WRONLY, 0644);
	write(fd, doc, ft_strlen(doc));
	free(doc);
	close(fd);
	fd = open("temp_file", O_RDONLY);
	dup2(hell->std_in, STDIN_FILENO);
	dup2(hell->std_err, STDERR_FILENO);
	unlink ("temp_file");
	unlink ("fd_checker");
	sig_setup_prompt();
	if (here && !ft_strncmp(limiter, here, ft_strlen(limiter)))
		return (doc_nelson(&here, temp, fd));
	else if (temp == 2)
		return (free_c(hell));
	else
		free_d(hell, temp);
	return (fd);
}
