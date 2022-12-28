/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarobert <rarobert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:12:30 by rarobert          #+#    #+#             */
/*   Updated: 2022/12/28 11:17:12 by rarobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free3d(char ***arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		ft_free_array(arr[i], (void *)arr[i]);
		i++;
	}
	free(arr);
}

int	ft_is_redirect(char *str)
{
	if (!(ft_strncmp(str, "<", 1)))
		return (1);
	if (!(ft_strncmp(str, "<<", 2)))
		return (1);
	if (!(ft_strncmp(str, ">", 1)))
		return (1);
	if (!(ft_strncmp(str, ">>", 2)))
		return (1);
	return (0);
}

void	print_3d(char ***arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			ft_printf("arr[%d][%d] = %s\n", i, j, arr[i][j]);
			j++;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	char	**split;
	char	***input;
	int		i;

	split = mini_split(argv[1], ' ');
	// while (split[++i])
	// 	ft_printf("split[%d] = %s\n", i, split[i]);
	if (argc != 2)
		ft_printf("error");
	else
		input = (rearrange_input(split));
	print_3d(input);
	ft_free_array(split, (void *)split);
	i = -1;
	while (input[++i])
		free (input[i]);
	free (input);
}
