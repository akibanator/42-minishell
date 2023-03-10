/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:47:45 by akenji-a          #+#    #+#             */
/*   Updated: 2023/03/10 15:45:45 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str [i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*join;
	unsigned int	i;
	unsigned int	len;

	len = ft_strlen(s1);
	join = malloc(len + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		join[len + i] = s2[i];
		i++;
	}
	join[len + i] = '\0';
	return (join);
}

char	*ft_strdup(char const *src)
{
	char	*aux;
	size_t	i;

	i = ft_strlen(src);
	aux = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (src[i++])
		aux[i - 1] = src[i - 1];
	aux[i - 1] = src[i - 1];
	if (aux != NULL)
		return (aux);
	else
		return (NULL);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	free(s1);
	return (join);
}

int	main(void)
{
	char	*doc;
	char	*str;
	int		i;

	i = 3;

	ft_printf("signal\n");
	doc = ft_strdup("");
	sig_setup_prompt();
	str = NULL;
	while (i--)
	{
		free(str);
		str = get_next_line(STDIN_FILENO);
		if (!str)
		{
			ft_printf("STR vazio\n");
			break;
		}
		doc = ft_strjoin_free(doc, str);
	}
	free(str);
	ft_printf("doc: %s\n", doc);
	ft_printf("return default signal\n");
	sig_setup_default();
	free(doc);
	return (0);
}
