/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:59:56 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/28 21:43:43 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_lst_void
{
	void				*content;
	struct s_lst_void	*next;
}					t_lst_void;

size_t		ft_strlen(const char *str);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t len);
int			ft_toupper(int c);
int			ft_tolower(int c);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t dsts);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_isspace(char c);
int			ft_atoi(const char *src);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strcharjoin(char *s1, char c);
char		*ft_strjoin_max(const char *str, ...);
char		*ft_concat_str(char *src, char *str);
char		*ft_concat_char(char *src, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
int			ft_putstr_fd(char *s, int fd);
int			ft_putstr(char *s);
void		ft_putendl_fd(char *s, int fd);
int			ft_putnbr_fd(int n, int fd);
int			ft_putnbr(int n);
int			ft_putchar_fd(char c, int fd);
int			ft_putchar(char c);
int			ft_intlen(long long nb);
int			ft_putunnbr_fd(unsigned int n, int fd);
int			ft_strnequal(const char *s1, const char *s2, size_t n);
int			ft_strequal(const char *s1, const char *s2);
void		ft_sort_param(int argc, char ***argv);
void		ft_swap_str(char *a, char *b);
int			ft_strcmp(char *s1, char *s2);

//chained list
t_lst_void	*ft_lstnew_void(void *content);
void		ft_lstadd_front_void(t_lst_void **alst, t_lst_void *new);
int			ft_lstsize_void(t_lst_void *lst);
t_lst_void	*ft_lstlast_void(t_lst_void *lst);
void		ft_lstadd_back_void(t_lst_void **alst, t_lst_void *new);
void		ft_lstdelone_void(t_lst_void *lst, void (*del)(void *));
void		ft_lstclear_void(t_lst_void **lst, void (*del)(void *));
void		ft_lstiter_void(t_lst_void *lst, void (*f)(void *));
t_lst_void	*ft_lstmap_void(t_lst_void *lst, void *(*f)(void *), \
														void (*del)(void *));
char		*ft_strtrim_void(char const *s1, char const *set);

#endif