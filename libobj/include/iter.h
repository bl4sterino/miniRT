/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:00:41 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/10 17:01:31 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_H
# define ITER_H

# include "obj.h"

int	obj_iter_push_v(t_obj_iter *self, t_obj_v v);
int	obj_iter_push_vn(t_obj_iter *self, t_obj_vn vn);
int	obj_iter_push_vt(t_obj_iter *self, t_obj_vt vt);

#endif
