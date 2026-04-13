/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:37:21 by pberne            #+#    #+#             */
/*   Updated: 2026/04/13 15:21:11 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_parse_texture(char *filepath, int malloc_id, t_list **object_lst)
{
	t_parsed_object	*new_object;

	new_object = ft_malloc_id(sizeof(t_parsed_object), malloc_id);
	ft_bzero(new_object, sizeof(t_parsed_object));
	new_object->type = object_type_texture_path;
	new_object->object.as_texture_path = ft_strdup_gc(filepath);
	ft_lstadd_front(object_lst, ft_lstnew_gc_id(new_object, malloc_id));
	return (1);
}

int	ft_try_parse_mat(t_material *mat, char **strs)
{
	if (!ft_atof_safe_0_255_to_0_1(strs[0], &mat->color.x))
		return (0);
	if (!ft_atof_safe_0_255_to_0_1(strs[1], &mat->color.y))
		return (0);
	if (!ft_atof_safe_0_255_to_0_1(strs[2], &mat->color.z))
		return (0);
	if (!ft_atof_safe_0_1(strs[3], &mat->diffusion))
		return (0);
	if (!ft_atof_safe_0_1(strs[4], &mat->reflectiveness))
		return (0);
	if (!ft_atof_safe(strs[5], &mat->emission))
		return (0);
	if (!ft_atof_safe(strs[6], &mat->refraction))
		return (0);
	if (!ft_atoi_safe(strs[7], &mat->color_tex))
		return (0);
	if (!ft_atoi_safe(strs[8], &mat->normal_tex))
		return (0);
	return (1);
}

int	ft_try_parse_texture(char **strs, int malloc_id, t_list **object_lst)
{
	t_material	mat;

	if (ft_strcmp(strs[0], "tex") == 0 && strs[1] && !strs[2])
		return (ft_parse_texture(strs[1], malloc_id, object_lst));
	if (ft_strcmp(strs[0], "obj") == 0 && strs[1])
	{
		ft_bzero(&mat, sizeof(t_material));
		if (strs[2] && strs[3] && strs[4] && strs[5] && strs[6] && strs[7]
			&& strs[8] && strs[9] && strs[10] && !strs[11])
		{
			if (!ft_try_parse_mat(&mat, &strs[2]))
				return (0);
		}
		return (ft_parse_obj(strs[1], malloc_id, object_lst, mat), 1);
	}
	else
		return (0);
}

// Extracts a texture to teh destination pointer,
// Exits if the extraction fails
void	ft_try_extract_texture(t_data *d, t_texture *out, char *filepath)
{
	t_texture	tex;
	int			useless;

	useless = 0;
	tex.ptr = mlx_xpm_file_to_image(d->mlx, filepath, &tex.width, &tex.height);
	if (tex.ptr == 0)
	{
		ft_putstr_fd("Cannot load texture: ", 2);
		ft_putstr_fd(filepath, 2);
		ft_exit_str_fd(1, "\n", 2);
	}
	tex.pixels = (int *)mlx_get_data_addr(tex.ptr, &useless, &useless,
			&useless);
	ft_add_exit(tex.ptr, ft_exit_destroy_image);
	*out = tex;
}
