/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:31:29 by pberne            #+#    #+#             */
/*   Updated: 2026/01/26 17:12:56 by pberne           ###   ########.fr       */
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
	int					rgb_int_color;
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

typedef struct s_parsed_object
{
	t_object_type		type;
	union				u_parsed_object
	{
		t_ambient_light	as_ambient_light;
		t_camera		as_camera;
		t_light			as_light;
		t_sphere		as_sphere;
		t_plane			as_plane;
		t_cylinder		as_cylinder;
	} object;
}						t_parsed_object;

typedef struct s_bounds
{
	t_v3d				min;
	t_v3d				max;
}						t_bounds;

typedef struct s_bvh_best_context
{
	int					axis;
	double				surface;
	int					left_id;
}						t_bvh_best_context;

/* Contains every scene object except Lights and Planes */
typedef struct s_object
{
	t_object_type		type;
	union				u_object
	{
		t_sphere		as_sphere;
		t_cylinder		as_cylinder;
	} object;
	t_bounds			bounds;
}						t_object;

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

typedef struct s_bvh_node
{
	t_bounds			bounds;
	int					split_axis;
	int					left;
	int					right;
	int					num_obj;
	int					start;
}						t_bvh_node;

typedef struct s_scene
{
	t_ambient_light		ambient_light;
	t_camera			camera;
	int					num_planes;
	t_plane				*planes;
	int					num_lights;
	t_light				*lights;
	int					num_objects;
	t_object			*objects;
	t_bvh_node			*bvh_nodes;
	int					bvh_node_capacity;
	int					bvh_root;
	int					bvh_node_count;
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
void					ft_extract_planes(t_scene *scene, t_list *lst);
void					ft_extract_objects(t_scene *scene, t_list *lst);

int						ft_bvh_builder(t_scene *scene, int start,
							int branch_elements);
void					ft_quicksort_objects(t_object *objs, int low, int high,
							int axis);
int						ft_partition(t_object *objs, int low, int high,
							int axis);
int						ft_get_longest_bounds_axis(t_bounds bounds);
double					ft_get_bounds_surface(t_bounds bounds);
int						ft_find_best_split(t_object *objs, int object_count,
							t_bounds range_bounds, int *left_elements);
t_bounds				ft_get_bounds_range(t_object *objects, int start,
							int branch_elements);

void					ft_process_objects_bounds(t_scene *scene);
t_bounds				ft_get_sphere_bounds(t_sphere sphere);

void					ft_normalize_vectors(t_list *scene);

#endif