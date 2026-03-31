/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:41:36 by pberne            #+#    #+#             */
/*   Updated: 2026/03/31 10:01:13 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_v3f	ft_get_object_movement(t_data *d)
{
	t_v3f	movement;
	float	boost;
	t_v3f	transformed_movement;
	float	yaw;

	boost = tn_f(ft_get_key(MOUSE_RIGHT, d), 5.0f, 1.0f);
	movement.x = ft_get_key(KEY_RIGHT, d) - ft_get_key(KEY_LEFT, d);
	movement.y = ft_get_key(KEY_KP_PLUS, d) - ft_get_key(KEY_KP_MINUS, d);
	movement.z = ft_get_key(KEY_UP, d) - ft_get_key(KEY_DOWN, d);
	if (ft_v3f_length_squared(movement) > EPSILON)
	{
		movement = ft_v3f_normalize(movement);
		movement = ft_v3f_scale(movement, OBJ_MOVEMENT_SPEED * boost
				* d->deltatime);
	}
	yaw = atan2f(d->scene->camera.direction.x, d->scene->camera.direction.z);
	transformed_movement = v3f(0.0f, 0.0f, 0.0f);
	transformed_movement.x += sinf(yaw) * movement.z;
	transformed_movement.z += cosf(yaw) * movement.z;
	transformed_movement.x += cosf(yaw) * movement.x;
	transformed_movement.z += -sinf(yaw) * movement.x;
	transformed_movement.y += movement.y;
	return (transformed_movement);
}

/* returns a rotation in degrees */
t_v3f	ft_get_object_rotation(t_data *d)
{
	t_v3f	rotation;

	rotation.x = ft_get_key(KEY_KP_DOT, d) - ft_get_key(KEY_KP_0, d);
	rotation.y = ft_get_key(KEY_KP_3, d) - ft_get_key(KEY_KP_2, d);
	rotation.z = ft_get_key(KEY_KP_6, d) - ft_get_key(KEY_KP_5, d);
	rotation = ft_v3f_scale(rotation, OBJ_ROTATION_SPEED * d->deltatime);
	return (rotation);
}

t_v3f	ft_get_object_extra(t_data *d)
{
	t_v3f	extra;

	extra.x = ft_get_key(KEY_KP_9, d) - ft_get_key(KEY_KP_8, d);
	extra.y = ft_get_key(KEY_KP_MULT, d) - ft_get_key(KEY_KP_DIV, d);
	extra.z = 0;
	extra = ft_v3f_scale(extra, OBJ_EXTRA_SPEED * d->deltatime);
	return (extra);
}
