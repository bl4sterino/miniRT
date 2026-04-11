/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:33:24 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/11 13:27:04 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "obj.h"

static void	fatal_obj(char *p, int fd, t_obj_iter *i)
{
	if (fd >= 0)
		close(fd);
	if (i)
		obj_iter_drop(i);
	ft_putstr_fd("Cannot load OBJ file: ", 2);
	ft_putstr_fd(p, 2);
	ft_exit_str_fd(1, "\n", 2);
}

static void	add_to_list(t_list **object_lst, int malloc_id, t_obj_f *f,
	t_material mat)
{
	t_parsed_object	*new_object;

	new_object = ft_malloc_id(sizeof(t_parsed_object), malloc_id);
	ft_bzero(new_object, sizeof(t_parsed_object));
	new_object->type = object_type_triangle;
	new_object->object.as_triangle = (t_triangle){
		.points = {{{f->verts[0].v.x, f->verts[0].v.y, -f->verts[0].v.z}},
	{{f->verts[1].v.x, f->verts[1].v.y, -f->verts[1].v.z}},
	{{f->verts[2].v.x, f->verts[2].v.y, -f->verts[2].v.z}}},
		.normals = {{{f->verts[0].vn.i, f->verts[0].vn.j, -f->verts[0].vn.k}},
	{{f->verts[1].vn.i, f->verts[1].vn.j, -f->verts[1].vn.k}},
	{{f->verts[2].vn.i, f->verts[2].vn.j, -f->verts[2].vn.k}}},
		.uvs = {{{f->verts[0].vt.u, 1.0f - f->verts[0].vt.v}},
	{{f->verts[1].vt.u, 1.0f - f->verts[1].vt.v}},
	{{f->verts[2].vt.u, 1.0f - f->verts[2].vt.v}}}};
	new_object->object.as_triangle = ft_get_processed_triangle(
			new_object->object.as_triangle);
	new_object->material = mat;
	ft_lstadd_back(object_lst, ft_lstnew_gc_id(new_object, malloc_id));
}

void	ft_parse_obj(char *filepath, int malloc_id, t_list **object_lst,
	t_material mat)
{
	t_obj_f		f;
	t_obj_iter	i;
	int			fd;
	t_io_res	r;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		fatal_obj(filepath, fd, NULL);
	r = obj_iter_new(&i, fd);
	if (r != IO_RES_OK)
		fatal_obj(filepath, fd, &i);
	while (1)
	{
		r = obj_iter_next(&i, &f);
		if (r == IO_RES_EOF)
			break ;
		if (r != IO_RES_OK)
			fatal_obj(filepath, fd, &i);
		add_to_list(object_lst, malloc_id, &f, mat);
	}
	obj_iter_drop(&i);
	close(fd);
}
