/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:36:34 by pberne            #+#    #+#             */
/*   Updated: 2026/01/19 11:34:46 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_get_fps_str_clean(double fps, char **fpsstr)
{
	char	*fpsstr_temp;

	fpsstr_temp = ft_dtoa_p(fps, 2);
	if (!fpsstr_temp)
		ft_exit(EXIT_FAILURE);
	if (*fpsstr)
		ft_free(*fpsstr);
	*fpsstr = ft_strjoin_gc("FPS: ", fpsstr_temp);
	free(fpsstr_temp);
	if (!fpsstr)
		ft_exit(EXIT_FAILURE);
}

int	ft_update_time(t_data *d)
{
	struct timeval	tv;
	static double	accumulated_time = 0;
	static double	frame_count = 0;
	static char		*fpsstr = 0;

	gettimeofday(&tv, 0);
	d->deltatime = (double)(tv.tv_sec - d->last_tv.tv_sec);
	d->deltatime += (double)(tv.tv_usec - d->last_tv.tv_usec) / 1000000.0;
	d->last_tv = tv;
	accumulated_time += d->deltatime;
	frame_count += 1.0;
	if (accumulated_time > DELTATIME_DISPLAY_DELAY)
	{
		ft_get_fps_str_clean(1.0 / (accumulated_time / frame_count), &fpsstr);
		accumulated_time = 0;
		frame_count = 0;
	}
	d->fpsstr = fpsstr;
	return (0);
}

double	ft_get_real_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}
