/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:02:54 by pberne            #+#    #+#             */
/*   Updated: 2026/02/25 15:15:56 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRUCTS_H
# define LIBFT_STRUCTS_H

# include "vectors.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_atof_data
{
	double			nb;
	int				i;
	double			sign;
	double			divider;
	int				is_decimal;
}					t_atof_data;

typedef union u_vnumber
{
	unsigned int	ui;
	int				i;
	float			f;
	double			d;
	long			l;
	unsigned long	ul;
}					t_vnumber;

/// VECTOR INT

typedef struct s_v2i
{
	int				x;
	int				y;
}					t_v2i;

typedef struct s_v3i
{
	int				x;
	int				y;
	int				z;
}					t_v3i;

/// VECTOR FLOAT

typedef struct s_v2f
{
	float			x;
	float			y;
}					t_v2f;

// Vector unsigned long

typedef struct s_v2ul
{
	unsigned long	x;
	unsigned long	y;
}					t_v2ul;

typedef struct s_v3ul
{
	unsigned long	x;
	unsigned long	y;
	unsigned long	z;
}					t_v3ul;

typedef struct s_read_file_context
{
	int				fd;
	char			buffer[4096];
	long			filesize;
	int				just_read;
	char			*out;
}					t_read_file_context;

#endif