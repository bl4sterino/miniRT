/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:27:54 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/06 16:29:38 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	rect_contains(t_rect rect, t_v2i pos)
{
	return (pos.x >= rect.x && pos.x < rect.x + rect.w
		&& pos.y >= rect.y && pos.y < rect.y + rect.h);
}
