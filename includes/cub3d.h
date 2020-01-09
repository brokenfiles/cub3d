/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:31:25 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/09 16:01:33 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "printf.h"
# include "keys.h"
# include "libft.h"
# include "get_next_line.h"
# include "structure.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "cub3d_defines.h"


//EVENTS
t_vector	rotation_matrice2(t_vector point, t_vector origin, float teta);
int			handle_key(int key, void *param);
//PARSING
int			parse_map(t_game *game, char *map_name);
int			fill_map(char *map_name, t_game *game);
int			get_int_len(unsigned int nb);
int			free_and_return(void *allocated, int ret);
int			is_structure_full(t_game *game);
char		*to_next_char(char *str, char c);
char		*get_val(char *line, char *key);
int			valid_map(t_game *game);
//DISPLAY
t_vector	next_inter(t_vector p, t_vector vec, float teta,
					   int *wall, t_game *game);
t_vector	next_hit(t_map *map, t_vector p, float teta,
					 int *wall, t_game *game, t_sprite *sprite, int x);
int			set_pixel_transparent(t_game *game,
									 t_vector pos, t_color color, float alpha);
int			render(t_game *game);
//DISPLAY_FORM
int			display_tri(t_game *game, t_form form);
int			display_rec(t_game *game, t_form form, t_image **image);
//DISPLAY_BONUS
int			display_bonus(t_game *game);


//OTHER
int save_image(t_game *game);


t_player	init_player();
t_game		*init_game();
t_form		form(t_vector vector, t_vector dim, int color);
t_image		*xpm_image(char *xpm, t_game *game);
t_image		*del_image(t_game *game, t_image *img);
t_image		*new_image(t_game *game, int w, int h);
t_color		c(int v);
t_color		get_pixel(t_image *image, int x, int y);
t_vector	vector(float x, float y);
void		ft_puterror(char *s);
void		image_set_pixel(t_image *image, int x, int y, int color);
int			display_cir2(t_game *game, t_form forme);
int			ft_scale(int ymin, int ymax, int nmin, int nmax, float y);
int			quit(t_game *game, int code, char *message);
int			test_line(t_game *game, t_form form,
						 float x_inter, int wall, float dist);
int			load_tex(t_game *game, t_image **image, char *tex);
int			convert_rgb(int r, int g, int b);
int			print_sprite(t_game *game, t_form form, float x_inter, float dist);
int			display_circle(t_game *game, t_form circle, float thick);
int			display_map(t_game *game, t_image **image);
int			update_map(t_game *game);
int			display_full_range(t_game *game);
int			centered_line(t_game *game, t_form form);
int			display_rec_trans(t_game *game, t_form form, t_image **image);
int			save_bitmap(t_game *game, char *name);
int			free_map(char **map, int counter);
#endif
