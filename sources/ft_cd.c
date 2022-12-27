/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 03:22:51 by akenji-a          #+#    #+#             */
/*   Updated: 2022/12/27 04:38:01 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "limits.h"

char	last_dir[PATH_MAX];

static char	*get_path(char *path, char *str)
{
	char	*path_pos;

	path_pos = path;
	ft_printf("path: %s\n", path);
	ft_printf("str: %s\n", str);
	while (*path != '\0')
		path++;
	while (*str != '\0')
	{
		*path = *str;
		path++;
		str++;
	}
	return (path_pos);
}

int		ft_cd(char *str)
{
	char	current_dir[PATH_MAX];
	char	path[PATH_MAX];

	ft_printf("PATH_MAX: %d\n", PATH_MAX);
	if (getcwd(current_dir, sizeof(current_dir)))
		*current_dir = '\0';
	ft_printf("current_dir: %s\n", current_dir);
	if (!ft_strlen(str))
		str = getenv("HOME");
	if (!ft_strcmp(str, "-"))
	{
		if (*last_dir == '\0')
		{
			ft_printf("nao ha diretorio anterior\n");
			return (1);
		}
		str = last_dir;
	} else {
		if (*str == '~')
		{
			if ((str[1] == '/') || (str[1] == '\0'))
			{
				ft_printf("str: %s\n", str);
				if (getcwd(path, sizeof(path)))
					str = get_path(path, ++str);
			}
		}
	}
	ft_printf("str: %s\n", str);
	return (0);
}