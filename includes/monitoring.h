/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:49:52 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 22:37:18 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITORING_H
# define MONITORING_H

# define CLOCK_COUNT 32

# define CLOCK_START 0
# define CLOCK_SET 1
# define CLOCK_GET 2
# define CLOCK_CLEAR 3
# define CLOCK_SET_GET 4

typedef enum e_clock_name
{
	clock_frame,
	clock_render,
	clock_loading,
	clock_reading
}		t_clock_name;

void	ft_clock_start(t_clock_name name);
void	ft_clock_set(t_clock_name name);
double	ft_clock_get(t_clock_name name);
void	ft_clock_clear(void);
double	ft_clock_set_and_get(t_clock_name name);

#endif
