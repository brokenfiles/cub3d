/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:31:25 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/03 13:53:33 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "printf.h"
# include "keys.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# define MIN_WIDTH 700
# define MIN_HEIGHT 700
# define NORTH 90
# define EAST 0
# define WEST 180
# define SOUTH -90

# include "structure.h"

void		ft_puterror(char *s);
int			quit(int code, char *message);
int			handle_key(int key, void *param);
int			fill_map(char *map_name, t_game *game);
int			display_rectangle(t_data *data, t_rectangle *rectangle);
int			display_map(t_game *game, t_image **image);
int			direction_change(t_player *player, float inc);
int			update_map(t_data *data, t_map *map, t_player *player);
int			display_triangle(t_data *data, t_triangle *triangle);
int			display_line(t_game *game, int x, float teta);
int			display_full_range(t_game *game);
int			display_tri(t_data *data, t_player *player, t_tri *triangle);
t_rectangle	*init_rectangle(t_dimension *dimension, t_vector *vector, int color);
t_triangle	*init_triangle(t_vector *vector1, t_vector *vector2, int color);
t_tri		*init_tri(t_vector *vector, int height, int color);
t_dimension	*init_dimension(int width, int height);
t_vector	*init_vector(int x, int y);
t_vector	*rotation_matrice(t_player *player, int x, int y);
int			init_player(t_player *player);
void		image_set_pixel(t_image *image, int x, int y, int color);
t_image		*del_image(t_game *game, t_image *img);
t_image		*new_image(t_game *game, int w, int h);
t_color		c(int v);
int			ft_lerpi(int first, int second, double p);
t_color		clerp(t_color c1, t_color c2, double p);
t_color		get_pixel(t_image *image, int x, int y);
t_image		*xpm_image(char *xpm, t_game *game);
t_image		*load_textures(t_game *game, t_image **image, char *texture);
#endif
