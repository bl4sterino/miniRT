/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 08:46:45 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 09:51:26 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl_data
{
	int					fd;
	char				*buff;
	int					pos;
	int					size;
	struct s_gnl_data	*next;
}						t_gnl_data;

char					*get_next_line(int fd);
char					*get_next_line_count(int fd, unsigned long *size);
t_gnl_data				*ft_get_gnl_data(int fd, t_gnl_data **data);
void					ft_clear_gnl_fd(int fd, t_gnl_data **data);
char					*ft_gnl_substr(char *str, int start,
							unsigned long size);
char					*ft_gnl_strjoin(char const *s1, char const *s2,
							size_t size1, size_t size2);
int						ft_gnl_strlen(char *str);
void					ft_clear_all_gnl_data(t_gnl_data **data);

char					*get_next_line_gc(int fd);
char					*get_next_line_count_gc(int fd, unsigned long *size);
char					*get_next_line_no_nl(int fd);
t_gnl_data				*ft_get_gnl_data_gc(int fd, t_gnl_data **data);
void					ft_clear_gnl_fd_gc(int fd, t_gnl_data **data);
char					*ft_gnl_substr_gc(char *str, int start,
							unsigned long size);
char					*ft_gnl_strjoin_gc(char const *s1, char const *s2,
							size_t size1, size_t size2);
int						ft_gnl_strlen_gc(char *str);
void					ft_clear_all_gnl_data_gc(t_gnl_data **data);

#endif