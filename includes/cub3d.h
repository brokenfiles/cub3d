/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:31:25 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/14 17:05:17 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "printf.h"
# include "keys.h"
# include "libft.h"
# include "get_next_line.h"
# include "cub3d_defines.h"
# include "structure.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>


//EVENTS
t_vector	rotation_matrice(t_vector point, t_vector origin, float teta);
int			handle_key(int key, void *param);
//MOVE
void		move(t_game *game, int key);
//INTERACTION
void		interact(t_game *game);
void		gain_life(t_game *game, int x, int y);
void		lose_life(t_game *game);
void		gain_coins(t_game *game, int x, int y);
void		level_up(t_game *game, int x, int y);
//PARSE MAP
int			load_default_textures(t_game *game);
int			parse_map(t_game *game, char *map_name);
int			fill_map(char *map_name, t_game *game);
int			valid_map(t_game *game);
//PARSE UTIL
int			get_resolution(t_game *game, char *line);
char		*get_val(char *line, char *key);
int			get_int_len(unsigned int nb);
int			is_structure_full(t_game *game);
char		*to_next_char(char *str, char c);
//PARSE FREE
int			free_and_return(void *allocated, int ret);
int			free_entire_map(char **str);
//PARSE TEX
int			get_color(t_game *game, char *line, char c);
int			get_texture(t_game *game, char *line, int *tex_counter);

//DISPLAY
t_vector	next_hit(t_map *map, t_vector p, float teta,
					 int *wall, t_game *game, t_sprite *sprites);
int			render(t_game *game);
//DISPLAY_SPRITE
void		clear_sprites(t_sprite *sprites, int n);
t_sprite	set_sprite(t_vector hit, int *wall, t_game *game);
int			display_sprite(t_game *game, t_sprite *sprites, int x, float angle);
//DISPLAY_FORM
int			display_tri(t_game *game, t_form form);
int			display_rec(t_game *game, t_form form, t_image **image);
int			display_rec_trans(t_game *game, t_form form, t_image **image);
int			display_cir2(t_game *game, t_form forme);
int			ft_scale(int ymin, int ymax, int nmin, int nmax, float y);
int			test_line(t_game *game, t_form form,
						 float x_inter, int wall, float dist);
int			print_sprite(t_game *game, t_form form, float x_inter, float dist, t_image *tex);
//DISPLAY_BONUS
int			display_bonus(t_game *game);
//TEXTURES
void		image_set_pixel(t_image *image, int x, int y, int color);
int			set_pixel_transparent(t_game *game,
									 t_vector pos, t_color color, float alpha);
t_image		*del_image(t_game *game, t_image *img);
t_image		*new_image(t_game *game, int w, int h);
void		put_image_to_image(t_image *image, t_image *layer, int x_pos, int y_pos);
t_image		*xpm_image(char *xpm, t_game *game);
int			load_tex(t_game *game, t_image **image, char *tex);
int			convert_rgb(int r, int g, int b);
t_image		*get_tex(t_game *game, char c);
//ERRORS
void		ft_puterror(char *s);
int			free_map(char **map, int counter);
int			quit(t_game *game, int code, char *message);
//HANDLER STRUCT
t_player	init_player();
void		reinit_player(t_game *game);
t_sprite	init_sprite();
t_game		*init_game();
void		init_level(t_game *game, int nb_level, char **av);
t_vector	vector(float x, float y);
t_form		form(t_vector vector, t_vector dim, int color);
//SAVE_IMG
int 		save_image(t_game *game);
//FT_ITOA
char	*ft_itoa(int nbr);
//MATRICE
t_vector	rotation_matrice(t_vector point, t_vector origin, float teta);
//OTHER
float		sq_dist(t_vector origin, t_vector point);


//A RANGER
t_color		c(int v);
t_color		get_pixel(t_image *image, int x, int y);
#endif
