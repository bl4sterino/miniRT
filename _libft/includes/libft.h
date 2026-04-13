/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:00:36 by pberne            #+#    #+#             */
/*   Updated: 2026/03/30 17:21:01 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define DOUBLE_PRINT_PRECISION 5
# define EPSILON 0.001f
# define FT_INFINITY 1.00000001504746622E30F
# define DEG2RAD 0.01745329251f
# define PI 3.14159265358979323846f

# ifndef M_PI
#  define M_PI 3.14159265358979323846f
# endif

# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923f
# endif

# include "clamp.h"
# include "dict.h"
# include "exit.h"
# include "ft_gc.h"
# include "ft_random.h"
# include "get_next_line.h"
# include "inlines.h"
# include "libft_structs.h"
# include "parser.h"
# include "utils.h"
# include "vectors.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_isalpha(char c);
int		ft_isdigit(char c);
int		ft_isalnum(char c);
int		ft_isascii(char c);
int		ft_isprint(char c);
int		ft_isspace(int c);
int		ft_get_next_space_index(char *str);
int		ft_str_has_only_c(char *str, char c);
int		ft_strhasc(const char *str, char c);
size_t	ft_strlen(const char *str);
size_t	ft_nblen(long nb);
int		ft_strclen(const char *str, char c);
int		ft_toupper(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);
int		ft_has_suffix(char *str, char *suffix);

int		ft_atoi(const char *str);
int		ft_atoi_safe(char *str, int *out);

float	ft_atof(char *str);
int		ft_atof_safe(char *str, float *dest);
int		ft_atof_safe_0_1(char *str, float *dest);
int		ft_atof_safe_0_255_to_0_1(char *str, float *dest);

int		ft_atoi_base(const char *str, char *base);
double	ft_atod(char *str);
int		ft_atod_safe(char *str, double *dest);
int		ft_atouc_safe(const char *str, unsigned char *out);
int		ft_atoc_safe(char *str, int *out);
int		ft_atod_safe_0_1(char *str, double *dest);
int		ft_atod_safe_0_255_to_0_1(char *str, double *dest);

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memset_int(void *s, int c, size_t n);
void	ft_bzero(void *b, size_t n);
void	*ft_memmove(void *dest, const void *start, size_t n);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strdup_gc(const char *s1);
char	*ft_strdup_gc_id(const char *s1, int id);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_calloc_gc(size_t nmemb, size_t size);
void	*ft_calloc_gc_id(size_t nmemb, size_t size, int id);
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_substr_gc(const char *str, unsigned int start, size_t len);
char	*ft_substr_gc_id(const char *str, unsigned int start, size_t len,
			int id);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_gc(char const *s1, char const *s2);
char	*ft_strjoin_gc_id(char const *s1, char const *s2, int id);

char	*ft_strjoin_mult(int nb, ...);
char	*ft_strjoin_mult_gc_id(int id, int nb, ...);
char	*ft_join_strs_gc_id(char **tab, char *separator, int id);
char	*ft_join_strs_gc(char **tab, char *separator);

char	*ft_strtrim(char const *s1, char const *set);
void	ft_str_replace(char *src, char *charset, char replacement);
char	**ft_split(char const *s, char c);
char	**ft_split_gc(char const *s, char c);
char	**ft_split_gc_id(char const *s, char c, int id);

char	*ft_itoa_r(long n, int depth, int *total_depth, int offset);
char	*ft_itoa(int n);
char	*ft_ltoa(long n);
char	*ft_ultoa(unsigned long n);
char	*ft_dtoa_p(double n, int decimals);
char	*ft_dtoa(double n);

char	*ft_itoa_gc(int n);
char	*ft_itoa_gc_id(int n, int id);
char	*ft_ltoa_gc(long n);
char	*ft_ultoa_gc(unsigned long n);
char	*ft_dtoa_p_gc(double n, int decimals);
char	*ft_dtoa_gc(double n);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
int		ft_putchar_fd(char c, int fd);
int		ft_putchar_ret(char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr_batch(int fd, ...);
int		ft_putstr_batch_ret(int fd, int ret, ...);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd_count(char *str, int fd);
int		ft_putnbr_base_l(long n, char *base);
int		ft_putnbr_base_ul(unsigned long n, char *base);
ssize_t	ft_write_all(int fd, const void *data, size_t len);

int		ft_printf(char *str, ...);

int		ft_putdouble(double n);
int		ft_putdouble_p(double n, int decimals);

void	ft_str_to_upper(char *str);
char	*ft_str_to_upper_gc(char *str);
void	ft_str_to_lower(char *str);
char	*ft_str_to_lower_gc(char *str);
char	*ft_str_to_lower_gc_id(char *str, int id);
char	*ft_str_to_upper_gc_id(char *str, int id);

/// LISTS

t_list	*ft_lstnew(void *content);
t_list	*ft_lstnew_gc(void *content);
t_list	*ft_lstnew_gc_id(void *content, int id);

void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstdelone_fr(t_list **lst, t_list *elem, void (*del)(void *));
void	ft_lstdelone_fr_gc(t_list **lst, t_list *elem, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstclear_gc(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstmerge(t_list *dest, t_list *src);
t_list	*ft_lstmerge_id(t_list *dest, t_list *src, int id);
t_list	*ft_lst_find(t_list *lst, int (*ft_cmp)(void *, void *),
			void *cmp_value);
void	ft_lstsort(t_list **begin_list, int (*cmp)(void *, void *));
char	*get_next_line(int fd);

long	ft_free_batch(long ret, int nb, ...);
long	ft_free_batch_gc(long ret, int nb, ...);

int		ft_putstr_fd_ret(char *s, int fd, int ret);
int		ft_equals(int a, int b);
int		ft_greater(int a, int b);
int		ft_smaller(int a, int b);
int		ft_differs(int a, int b);
int		ft_min(int a, int b);
int		ft_max(int a, int b);
int		ft_minv(unsigned int i, ...);
int		ft_maxv(unsigned int i, ...);
int		ft_sign(int nb);
double	ft_sign_d(double nb);
int		ft_abs(int a);
void	ft_free_split(char **tab);
void	ft_free_split_gc(char **tab);
int		ft_clampi(int nb, int min, int max);
long	ft_clampl(long nb, long min, long max);
float	ft_clampf(float nb, float min, float max);
double	ft_clampd(double nb, double min, double max);

void	ft_swapi(int *a, int *b);
void	ft_swapl(long *a, long *b);
void	ft_swapul(unsigned long *a, unsigned long *b);
void	ft_swapf(float *a, float *b);
void	ft_swapd(double *a, double *b);

char	*ft_read_file_gc_id(char *filepath, int malloc_id);

#endif
