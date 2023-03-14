/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:50:53 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/14 04:17:17 by akenji-a         ###   ########.fr       */
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

static void	free_c(t_hell *hell)
{
	//ft_free_nelson(hell->nelson);
	t_nelson	*aux;

	aux = hell->nelson;
	while (hell->nelson->next)
	{
		hell->nelson = hell->nelson->next;
		ft_free_array(hell->nelson->content, (void *)hell->nelson->content);
	}
	hell->nelson = aux;
	hell->nelson->next = NULL;
}

static void	free_d(t_hell *hell)
{
	char	*str;
	char	*line;

	str = ft_strdup("warning: here-document at line ");
	line = ft_itoa(hell->lines);
	str = ft_strjoin_free(str, line);
	cmd_error("", str, 1);
	free(str);
	free(line);
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
		free_c(hell);
	else
		free_d(hell);
	write(2, "\n", 1);
	return (fd);
}
