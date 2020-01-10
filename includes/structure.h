/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 12:59:47 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/10 16:50:56 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct	s_rgba
{
	uint8_t		b;
	uint8_t		g;
	uint8_t		r;
	uint8_t		a;
}				t_rgba;
typedef union	u_color
{
	int			value;
	t_rgba		rgba;
}				t_color;
typedef struct	s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
	int			width;
	int			height;
}				t_image;
typedef struct	s_vector
{
	float		x;
	float		y;
}				t_vector;
typedef struct	s_form
{
	t_vector	dim;
	t_vector	vector;
	int			color;
}				t_form;
typedef struct	s_tex
{
	t_image		*no_tex;
	t_image		*so_tex;
	t_image		*we_tex;
	t_image		*ea_tex;
	t_image		*sp_tex;
	t_image		*li_tex;
	t_image		*do_tex;
	t_image		*co_tex;
	t_image		*lu_tex;
	t_image		*sky_tex;
	t_image		*floor_tex;
	t_image		*nbrs[10];
	char		*sky_color;
	char		*floor_color;
	int			size;
}				t_tex;
typedef struct	s_map
{
	char		**map;
	int			lines;
	float		spawn_yaw;
	int			sky_color;
	int			floor_color;
	t_vector	spawn;
	t_tex		tex;
}				t_map;
typedef struct	s_player
{
	t_vector	pos;
	int			yaw;
	float		speed;
	int			rot_speed;
	float		health;
	int			coins;
	char		*coins_str;
	float		size;
}				t_player;
typedef struct	s_sprite
{
	t_vector	pos;
	int			wall;
	int			defined;
	t_image		*tex;
}				t_sprite;
typedef struct	s_game //pq est ce que la structure t_tex est rangée dans map et pas directement dans game ? peut etre pour avoir differentes maps avec des textures associées?
{
	void		*ptr;
	void		*win;
	t_map		*map;
	t_player	p;
	t_image		*image;
	int			save_first_image;
	int			disable_map;
}				t_game;
#endif
