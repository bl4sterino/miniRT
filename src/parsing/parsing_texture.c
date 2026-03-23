/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:37:21 by pberne            #+#    #+#             */
/*   Updated: 2026/03/23 19:15:31 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_parse_texture(char *filepath, int malloc_id, t_list **object_lst)
{
	t_parsed_object	*new_object;

	new_object = ft_malloc_id(sizeof(t_parsed_object), malloc_id);
	ft_bzero(new_object, sizeof(t_parsed_object));
	new_object->type = object_type_texture_path;
	new_object->object.as_texture_path = filepath;
	ft_lstadd_back(object_lst, ft_lstnew_gc_id(new_object, malloc_id));
	return (1);
}

int	ft_try_parse_texture(char **strs, int malloc_id, t_list **object_lst)
{
	if (ft_strcmp(strs[0], "tex") == 0 && strs[1] && !strs[2])
		return (ft_parse_texture(strs[1], malloc_id, object_lst));
	else
		return (0);
}

void	ft_load_textures(t_data *d, t_scene *scene, t_list *lst)
{
	int				i;
	t_parsed_object	*po;
	int				useless;

	scene->num_textures = ft_count_matches(lst, object_type_texture_path);
	if (scene->num_textures == 0)
		return ;
	scene->num_textures += 2;
	scene->textures = ft_malloc(sizeof(t_texture) * scene->num_textures);
	ft_bzero(scene->textures, sizeof(t_texture) * scene->num_textures);
	i = 2;
	while (lst)
	{
		po = lst->content;
		if (po->type == object_type_texture_path)
		{
			scene->textures[i].ptr = mlx_xpm_file_to_image(d->mlx,
					po->object.as_texture_path, &scene->textures[i].width,
					&scene->textures[i].height);
			if (scene->textures[i].ptr == 0)
			{
				ft_putstr_fd("Cannot load texture: ", 2);
				ft_putstr_fd(po->object.as_texture_path, 2);
				ft_exit_str_fd(1, "\n", 2);
			}
			scene->textures[i].pixels = mlx_get_data_addr(scene->textures[i].ptr,
					&useless, &useless, &useless);
			ft_add_exit(scene->textures[i].ptr, ft_exit_destroy_image);
			i++;
		}
		lst = lst->next;
	}
}
