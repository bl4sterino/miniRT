/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:31:29 by pberne            #+#    #+#             */
/*   Updated: 2026/01/22 14:51:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_DATA_H
# define SCENE_DATA_H

# include "rt.h"

/// OBJECTS STRUCTS

typedef struct s_ambient_light
{
	double				intensity;
	t_v3d				color;
}						t_ambient_light;

typedef struct s_camera
{
	t_v3d				position;
	t_v3d				direction;
	double				fov;
}						t_camera;

typedef struct s_light
{
	t_v3d				position;
	double				intensity;
	t_v3d				color;
}						t_light;

typedef struct s_sphere
{
	t_v3d				position;
	double				radius;
	t_v3d				color;
}						t_sphere;

typedef struct s_plane
{
	t_v3d				position;
	t_v3d				normal;
	t_v3d				color;
}						t_plane;

typedef struct s_cylinder
{
	t_v3d				position;
	t_v3d				normal;
	double				diameter;
	double				height;
	t_v3d				color;
}						t_cylinder;

/// OBJECTS ENUM

typedef enum e_object_type
{
	object_type_ambient_light,
	object_type_camera,
	object_type_light,
	object_type_sphere,
	object_type_plane,
	object_type_cylinder
}						t_object_type;

/// OBJECTS UNION

typedef union u_object
{
	t_ambient_light		as_ambient_light;
	t_camera			as_camera;
	t_light				as_light;
	t_sphere			as_sphere;
	t_plane				as_plane;
	t_cylinder			as_cylinder;
}						t_object;

typedef struct s_object_element
{
	t_object_type		type;
	t_object			object;
}						t_object_element;

typedef struct s_struct_parser_data
{
	t_object_type		type;
	t_list				*lst;
}						t_struct_parser_data;

typedef struct s_scene_parsing_context
{
	int					fd;
	char				*line;
	t_dict				*dict;
	char				**strs;
	t_list				*object_lst;
	int					line_count;
}						t_scene_parsing_context;

typedef struct s_scene
{
	t_ambient_light		ambient_light;
	t_camera			camera;
	int					num_spheres;
	t_sphere			*spheres;
	int					num_planes;
	t_plane				*planes;
	int					num_cylinders;
	t_cylinder			*cylinders;
	int					num_lights;
	t_light				*lights;
}						t_scene;

/// METHODS

t_scene					*ft_parse_map(char *finename);
t_dict					*ft_setup_parsing_dict(t_dict *dict, int malloc_id);
t_parsing_data			*ft_get_pdata(int malloc_id, t_parsing_data d);

// PARSERS

void					ft_parsing_error_on_line(int n);

t_struct_parser_data	*ft_get_parser_ambient_light(int id);
t_struct_parser_data	*ft_get_parser_camera(int id);
t_struct_parser_data	*ft_get_parser_light(int id);
t_struct_parser_data	*ft_get_parser_sphere(int id);
t_struct_parser_data	*ft_get_parser_plane(int id);
t_struct_parser_data	*ft_get_parser_cylinder(int id);

void					ft_extract_camera(t_scene *scene, t_list *lst);
void					ft_extract_ambient_light(t_scene *scene, t_list *lst);
void					ft_extract_lights(t_scene *scene, t_list *lst);
void					ft_extract_spheres(t_scene *scene, t_list *lst);
void					ft_extract_planes(t_scene *scene, t_list *lst);
void					ft_extract_cylinder(t_scene *scene, t_list *lst);

void					ft_normalize_vectors(t_scene *scene);

#endif