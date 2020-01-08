/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:56:51 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/06 09:52:50 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef	struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_lstsize(t_list *lst);
int					ft_atoi(const char *str);
char				*ft_strnstr(const char *haystack,
		const char *needle, size_t n);
size_t				ft_strlen(const char *str);
int					ft_strcmp(const char *str1, const char *str2);
int					ft_strncmp(const char *str1, const char *str2, size_t nb);
char				*ft_strrchr(char const *str, int c);
char				*ft_strchr(const char *s, int c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strncat(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t size);
char				*ft_strdup(const char *s1);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char *));
int					ft_stronly(const char *s, const char *s2);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_substr(char const *s1, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s, char const *set);
char				**ft_split(char *str, char *charset);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_power(int nb, int pow);
int					ft_memcmp(const void *s1, const void *s2, size_t size);
void				*ft_memchr(const void *s, int c, size_t size);
void				*ft_memmove(void *dest, const void *src, size_t size);
void				*ft_memccpy(void *dest, const void *src, int c,
		size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t size);
void				*ft_memset(void *s, int c, size_t size);
void				ft_bzero(void *s, size_t size);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstnew(void *content);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
		void (*del)(void *));
void				ft_lstrev(t_list **alst);
t_list				*ft_lstlast(t_list *lst);
#endif
