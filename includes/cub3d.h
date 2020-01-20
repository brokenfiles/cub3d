/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:31:25 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/20 13:19:03 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "keys.h"
# include "libft.h"
# include "get_next_line.h"
# include "cub3d_defines.h"
# include "structure.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

int			handle_key(int key, void *param);
int			direction_change(t_player *player, int sign);
void		change_rot_speed(t_game *game, int key);
void		move(t_game *game, int key);
void		interact(t_game *game, int key);
void		gain_life(t_game *game, int x, int y);
void		lose_life(t_game *game);
void		gain_coins(t_game *game, int x, int y);
void		level_up(t_game *game, int x, int y);
void		display_step(t_game *game);
t_vector	next_hit(t_game *game, t_ray *ray);
float		calc_inter2(t_ray *r, t_sprite *sp);
void		clear_sprites(t_sprite *sprites, int n);
t_sprite	set_sprite(t_vector hit, int *wall, t_game *game);
int			display_sprite(t_game *game, t_ray *r, int x);
int			display_tri(t_game *game, t_form form);
int			display_rec(t_game *game, t_form form, t_image **image, int t);
int			display_cir2(t_game *game, t_form forme, int t);
int			display_rec_deg(t_game *game, t_form form,
		int t, int color);
void		print_line(t_game *game, t_form f, t_ray *ray);
void		display_map(t_game *game, t_image **image, int t);
int			display_bonus(t_game *game, int t);
int			render(t_game *game);
void		image_set_pixel(t_image *image, int x, int y, int color);
int			set_pixel_transparent(t_game *game, t_vector pos, t_color color,
									float alpha);
t_image		*del_image(t_game *game, t_image *img);
t_image		*new_image(t_game *game, int w, int h);
void		put_image_to_image(t_image *image, t_image *layer, t_vector pos,
		float k);
t_image		*xpm_image(char *xpm, t_game *game);
int			load_tex(t_game *game, t_image **image, char *tex);
t_image		*get_tex(t_game *game, char c);
void		ft_puterror(char *s);
int			free_map(char **map, int counter);
int			quit(int code, char *message);
int			fnq(void (*f)(void *), void *mem, int code, char *message);
int			close_red_button();
t_player	init_player();
void		reinit_player(t_game *game);
int			init_ray(t_ray *ray, float teta);
t_sprite	init_sprite();
t_game		*init_game();
void		init_level(t_game *game, int nb_level, char **av);
int			save_image(t_game *game);
char		*ft_itoa(int nbr);
t_vector	rotation_matrice(t_vector point, t_vector origin, float teta);
float		sq_dist(t_vector origin, t_vector point);
int			ft_scale(t_vector y_x, t_vector n_v, float y);
int			ft_scale2(int ymin, int ymax, int nmax, float y);
int			conv_rgb(int r, int g, int b, float k);
t_vector	vec(float x, float y);
t_form		form(t_vector vector, t_vector dim, int color);
t_color		c(int v);
t_color		get_pixel(t_image *image, int x, int y);
int			load_default_textures(t_game *game);
int			parse_map(t_game *game, char *map_name);
int			fill_map(char *map_name, t_game *game);
int			valid_map(t_game *game);
int			free_entire_parsing(t_game *game);
int			load_nbrs(t_game *game);
int			init_tex(t_game *game);
int			remove_spaces(char **line);
int			get_resolution(t_game *game, char *line);
char		*get_val(char *line, char *key);
int			get_int_len(unsigned int nb);
int			is_structure_full(t_game *game);
char		*to_next_char(char *str, char c);
int			free_and_return(void *allocated, int ret);
void		free_entire_map(void *mem);
int			get_color(t_game *game, char *line, char c);
int			get_texture(t_game *game, char *line, int *tc);
#endif
