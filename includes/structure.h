/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 12:59:47 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/17 17:40:21 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct			s_rgba
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
	uint8_t	a;
}						t_rgba;
typedef union			u_color
{
	int		value;
	t_rgba	rgba;
}						t_color;
typedef struct			s_image
{
	void	*image;
	char	*ptr;
	int		bpp;
	int		stride;
	int		endian;
	int		width;
	int		height;
}						t_image;
typedef struct		s_vector
{
	float	x;
	float	y;
}					t_vector;
typedef struct		s_tex
{
	t_image		*no;
	t_image		*so;
	t_image		*we;
	t_image		*ea;
	t_image		*sp;
	char		*sky_color;
	char		*floor_color;
	int			wall_color;
	int			void_color;
	int			p_color;
	int			size;
}					t_tex;
typedef struct		s_map
{
	char		**map;
	int			lines;
	t_vector	spawn;
	t_tex		tex;
}					t_map;
typedef struct		s_player
{
	t_vector	*pos;
	t_vector	*dir;
	float		speed;
	int			rot_speed;
	float		health;
	float		size;
}					t_player;
typedef struct		s_ray
{
	float		x;
	float		y;
	float		mov_x;
	float		mov_y;
	float		dx;
	float		dy;
	int			map_x;
	int			map_y;
	int			height;
	int			side;
	float		dist;
	float		light;
//	t_image		*texture;
//	int			tex_x;
//	float		fx;
//	float		fy;
}					t_ray;
typedef struct		s_game
{
	void		*ptr;
	void		*win;
	t_image		*image;
	t_map		*map;
	t_player	*p;
	int			save_first_image;
}					t_game;
#endif
