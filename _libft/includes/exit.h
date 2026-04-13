/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:11:00 by pberne            #+#    #+#             */
/*   Updated: 2026/01/22 14:48:32 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# define OPEN_FAILED 3
# define MALLOC_FAILED 4
# define ADD_EXIT -1

typedef struct s_exit_data
{
	void	*d;
	void	(*f)(void *);
}			t_exit_data;

void		ft_add_exit(void *d, void (*f)(void *));
void		ft_exit(int exit_code);
void		ft_exit_str_fd(int exit_code, char *str, int fd);

// EXIT UTILS

void		ft_exit_close_fd(void *fd);

#endif
