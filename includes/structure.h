/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 12:59:47 by llaurent          #+#    #+#             */
/*   Updated: 2019/11/28 19:00:40 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct		s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		width;
	int		height;
}					t_data;
typedef struct		s_location
{
	float	x;
	float	y;
	int		yaw;
}					t_location;
typedef struct		s_vector
{
	int	x;
	int	y;
}					t_vector;
typedef struct		s_dimension
{
	int	height;
	int	width;
}					t_dimension;
typedef struct		s_rectangle
{
	t_dimension	*dimension;
	t_vector	*vector;
	int			color;
}					t_rectangle;
typedef struct		s_triangle
{
	t_vector	*vector1;
	t_vector	*vector2;
	int			color;
}					t_triangle;
typedef struct      s_tri
{
    
    t_vector *vector;
    int height;
    int color;
}                   t_tri;


typedef struct		s_texture
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*sp_texture;
	char		*sky_color;
	char		*floor_color;
}					t_texture;
typedef struct		s_map
{
	char		**map;
	int			lines;
	t_location	spawn;
	t_texture	textures;
}					t_map;
typedef struct		s_player
{
	float		health;
	t_location	location;
	float		size;
	float		speed;
	int			rotation_speed;
}					t_player;
typedef struct		s_game
{
	t_data		*data;
	t_map		*map;
	t_player	*player;
}					t_game;
#endif
