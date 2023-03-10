/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 01:09:47 by rarobert          #+#    #+#             */
/*   Updated: 2023/03/10 15:46:06 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list_gnl {
	char				*str;
	struct s_list_gnl	*next;
}	t_list_gnl;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//get_next_line
char		get_next_char(int fd);
char		*get_next_line(int fd);
char		*get_string(t_list_gnl *lst, size_t len);
int			ft_dec_lst_size(t_list_gnl *lst);
void		ft_lstclear_gnl(t_list_gnl *lst);
void		fill_list(int fd, t_list_gnl *to_fill);
t_list_gnl	*ft_lstnew_gnl(void);

//ft_printf
int			ft_printf(const char *str, ...);
int			call_charlie(int c);
int			call_stacy(char *str);
int			call_intelligence(int nb);
int			call_unintelligence(unsigned int nb);
int			call_poncho(unsigned long long int nb);
int			call_professor(unsigned int nb, char c);
int			telefonist(va_list contacts, char who_to_call);

void		sig_setup_prompt(void);
void		sig_setup_default(void);

#endif
