/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 12:59:47 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/16 14:21:01 by llaurent         ###   ########.fr       */
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
	int			w;
	int			h;
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
	t_image		*m_enter_tex;
	t_image		*m_g_o_tex;
	t_image		*m_n_tex;
	t_image		*logo_tex;
	t_image		**nbrs;
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
	int			vision;
	float		speed;
	int			rot_speed;
	float		health;
	int			coins;
	float		size;
}				t_player;
typedef struct	s_sprite
{
	t_vector	pos;
	int			wall;
	int			defined;
	t_image		*tex;
}				t_sprite;
typedef struct	s_ray
{
	float		alpha;
	float		cos;
	float		sin;
	float		tan;
	t_vector	pos;
	int			wall;
	float		dist;
	float		inter;
	int			sp_num;
	t_sprite	*sprites;
}				t_ray;
typedef struct	s_game
{
	void		*ptr;
	void		*win;
	t_map		*map;
	t_player	p;
	t_vector	dim;
	t_image		*image;
	float		angle;
	int			step;
	int			save_first_image;
	int			disable_map;
	int			disable_bonus;
	int			level;
	int			total_level;
	char		*level_names[MAX_LEVEL];
}				t_game;
#endif
