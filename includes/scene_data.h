/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:31:29 by pberne            #+#    #+#             */
/*   Updated: 2026/04/04 15:39:08 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_DATA_H
# define SCENE_DATA_H

# include "rt.h"

/// OBJECTS STRUCTS

typedef struct s_material
{
	t_v3f				color;
	float				diffusion;
	float				reflectiveness;
	float				reflectiveness_rand;
	float				emission;
	float				refraction;
	int					color_tex;
	int					normal_tex;
}						t_material;

typedef struct s_ambient_light
{
	float				intensity;
	t_v3f				color;
	int					rgb_int_color;
	float				fog_density;
	int					ray_bounce;
}						t_ambient_light;

typedef struct s_camera
{
	t_v3f				position;
	t_v3f				direction;
	float				fov;
}						t_camera;

typedef struct s_skybox
{
	int					color;
	int					luminance;
}						t_skybox;

typedef struct s_light
{
	t_v3f				position;
	float				intensity;
	t_v3f				color;
}						t_light;

typedef struct s_sphere
{
	t_v3f				position;
	float				radius;
}						t_sphere;

typedef struct s_plane
{
	t_v3f				position;
	t_v3f				normal;
}						t_plane;

typedef struct s_cylinder
{
	t_v3f				position;
	t_v3f				normal;
	t_v3f				top_center;
	float				diameter;
	float				radius;
	float				height;
}						t_cylinder;

typedef struct s_quad
{
	t_v3f				position;
	t_v3f				normal;
	t_v2f				size;
	t_v3f				u_axis;
	t_v3f				v_axis;
}						t_quad;

typedef union u_tri_points
{
	struct
	{
		t_v3f			a;
		t_v3f			b;
		t_v3f			c;
	};
	t_v3f				p[3];
}						t_tri_points;

typedef struct s_triangle
{
	t_v3f				position;
	t_v3f				normal;
	t_tri_points		points;
}						t_triangle;

typedef struct s_ellipsoid
{
	t_v3f				position;
	t_v3f				radii;
	t_v3f				inv_r2;
}						t_ellipsoid;

/// OBJECTS ENUM

typedef enum e_object_type
{
	object_type_ambient_light,
	object_type_camera,
	object_type_light,
	object_type_plane,
	object_type_sphere,
	object_type_cylinder,
	object_type_quad,
	object_type_triangle,
	object_type_ellipsoid,
	object_type_texture_path,
	object_type_skybox
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
		t_quad			as_quad;
		t_triangle		as_triangle;
		t_ellipsoid		as_ellipsoid;
		t_skybox		as_skybox;
		char			*as_texture_path;
	} object;
	t_material			material;
}						t_parsed_object;

typedef union u_bounds
{
	struct
	{
		t_v3f			min;
		t_v3f			max;
	};
	t_v3f				v[2];
}						t_bounds;

typedef struct s_bvh_best_context
{
	int					axis;
	float				surface;
	int					left_id;
	int					iterator;
}						t_bvh_best_context;

/* Contains every scene object except Lights and camera */
typedef struct s_object
{
	t_object_type		type;
	union				u_object
	{
		t_sphere		as_sphere;
		t_cylinder		as_cylinder;
		t_plane			as_plane;
		t_quad			as_quad;
		t_triangle		as_triangle;
		t_ellipsoid		as_ellipsoid;
		t_light			as_light;
	} object;
	t_material			material;
	t_bounds			bounds;
	float				pdf;
	int					raw_id;
}						t_object;

typedef struct s_struct_parser_data
{
	t_object_type		type;
	t_list				*element_lst;
	t_list				*material_lst;
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

typedef struct s_bounds2x
{
	t_v3f				min_x;
	t_v3f				max_x;
	t_v3f				min_y;
	t_v3f				max_y;
	t_v3f				min_z;
	t_v3f				max_z;
}						t_bounds2x;

typedef struct s_bvh_node
{
	t_bounds2x			bounds2x;
	t_bounds			bounds;
	int					split_axis;
	int					left;
	int					right;
	int					num_obj;
	int					start;
}						t_bvh_node;

typedef struct s_texture
{
	void				*ptr;
	int					*pixels;
	t_v3f				*hdr_pixels;
	int					width;
	int					height;
}						t_texture;

typedef struct s_scene
{
	t_ambient_light		ambient_light;
	t_camera			camera;
	t_texture			skybox_tex;
	t_sphere			skybox_sphere;
	int					num_planes;
	t_object			*planes;
	int					num_lights;
	t_light				*lights;
	int					num_objects;
	int					emissive_objects;
	int					total_emissive_count;
	t_object			*objects;
	t_object			*raw_objects;
	t_bvh_node			*bvh_nodes;
	int					bvh_node_capacity;
	int					bvh_root;
	int					bvh_node_count;
	int					num_textures;
	t_texture			*textures;
}						t_scene;

typedef struct s_data	t_data;

/// METHODS

t_scene					*ft_parse_map(t_data *d, char *filename);
t_dict					*ft_setup_parsing_dict(t_dict *dict, int malloc_id);
t_parsing_data			*ft_get_pdata(int malloc_id, t_parsing_data d);

// PARSERS

void					ft_parsing_error_on_line(int n);

t_struct_parser_data	*ft_get_parser_ambient_light(int id);
t_struct_parser_data	*ft_get_parser_camera(int id);
t_struct_parser_data	*ft_get_parser_light(int id);
t_list					*ft_get_parser_material(int id);
t_struct_parser_data	*ft_get_parser_sphere(int id);
t_struct_parser_data	*ft_get_parser_plane(int id);
t_struct_parser_data	*ft_get_parser_cylinder(int id);
t_struct_parser_data	*ft_get_parser_quad(int id);
int						ft_try_parse_texture(char **strs, int malloc_id,
							t_list **object_lst);
void					ft_load_textures(t_data *d, t_scene *scene,
							t_list *lst);
void					ft_try_extract_texture(t_data *d, t_texture *out,
							char *filepath);
void					ft_create_hdr_tex(t_texture *out,
							t_texture *color, t_texture *lum);

t_cylinder				ft_get_processed_cylinder(t_cylinder cyl);
t_quad					ft_get_processed_quad(t_quad quad);
t_struct_parser_data	*ft_get_parser_triangle(int id);
t_triangle				ft_get_processed_triangle(t_triangle tri);
t_struct_parser_data	*ft_get_parser_ellipsoid(int id);
t_ellipsoid				ft_get_processed_ellipsoid(t_ellipsoid el);
t_struct_parser_data	*ft_get_parser_skybox(int id);

long					ft_count_matches(t_list *lst, t_object_type type);

void					ft_extract_camera(t_scene *scene, t_list *lst);
void					ft_extract_ambient_light(t_scene *scene, t_list *lst);
void					ft_extract_skybox(t_scene *scene, t_list *lst);
void					ft_extract_lights(t_scene *scene, t_list *lst);
void					ft_extract_planes(t_scene *scene, t_list *lst);
void					ft_extract_objects(t_scene *scene, t_list *lst);

t_bounds				ft_get_sphere_bounds(t_sphere sphere);
t_bounds				ft_get_cylinder_bounds(t_cylinder cyl);
t_bounds				ft_get_quad_bounds(t_quad quad);
t_bounds				ft_get_triangle_bounds(t_triangle tri);
t_bounds				ft_get_ellipsoid_bounds(t_ellipsoid el);

void					ft_setup_emissive_objects(t_scene *scene);
void					ft_preprocess_pdfs(t_scene *scene);

int						ft_update_bvh(t_scene *scene, int start,
							int branch_elements);
int						ft_bvh_new_node(t_scene *scene);
int						ft_bvh_builder(t_scene *scene, int start,
							int branch_elements);
void					ft_swap_objects(t_object *a, t_object *b);
void					ft_quicksort_objects(t_object *objs, int low, int high,
							int axis);
int						ft_partition(t_object *objs, int low, int high,
							int axis);
int						ft_get_longest_bounds_axis(t_bounds bounds);
float					ft_get_bounds_surface(t_bounds bounds);
int						ft_find_best_split(t_object *objs, int object_count,
							t_bounds range_bounds, int *left_elements);
t_bounds				ft_get_bounds_range(t_object *objects, int start,
							int branch_elements);

void					ft_process_objects_bounds(t_scene *scene);

void					ft_normalize_vectors(t_list *scene);

#endif
