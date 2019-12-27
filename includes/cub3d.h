/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:31:25 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/16 15:34:59 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "printf.h"
# include "keys.h"
# include "libft.h"
# include "structure.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# define MIN_WIDTH 500
# define MIN_HEIGHT 500
# define NORTH 90
# define EAST 0
# define WEST 180
# define SOUTH -90
# define MAP_SIZE 190
# define MINIMAP_PLAYER_COLOR 0xA896FF
# define AIM_HEIGHT 25
# define AIM_WIDTH 2
# define AIM_COLOR 0xFFFFFF
# define GAME_NAME "cub3d"
# define ARGUMENT_SAVE "-save"
# define ARGUMENT_DISABLE_MAP "--disable-map"
# define MSG_MAP_ERROR "Invalid map."
# define MSG_RENDERING_ERROR "Rendering error."
# define MSG_RENDERING_ERROR_428 "Rendering error. (ERROR_CODE 428)"
# define MSG_RENDERING_ERROR_429 "Rendering error. (ERROR_CODE 429)"
# define MSG_TOO_FEW_ARGUMENTS "Too few arguments.\nUsage: ./cub3d <valid map>"
# define MSG_CANNOT_ALLOCATE_GAME_ERROR "Cannot allocate global game."
# define MSG_CANNOT_ALLOCATE_MAP_ERROR "Cannot allocate map."
# define MSG_CANNOT_ALLOCATE_IMAGE_ERROR "Cannot allocate image."
# define MSG_CANNOT_ALLOCATE_PLAYER_ERROR "Cannot allocate player."
# define MSG_CANNOT_INIT_MLX_ERROR "Cannot init MLX."
# define MSG_CANNOT_INIT_MLX_WINDOW_ERROR "Cannot init MLX's window."

void		ft_puterror(char *s);
int			quit(t_game *game, int code, char *message);
int			fill_map(char *map_name, t_game *game);
void		image_set_pixel(t_image *image, int x, int y, int color);
t_image		*del_image(t_game *game, t_image *img);
t_image		*new_image(t_game *game, int w, int h);
t_color		c(int v);
int			ft_scale(int ymin, int ymax, int nmin, int nmax, float y);
int			test_line(t_game *game, t_form form, float x_inter, int wall, float dist);
int			display_aim(t_game *game);
int			ft_lerpi(int first, int second, double p);
t_color		clerp(t_color c1, t_color c2, double p);
t_color		get_pixel(t_image *image, int x, int y);
t_image		*xpm_image(char *xpm, t_game *game);
t_image		*load_tex(t_game *game, t_image **image, char *tex);
int 		convertRGB(int R, int G, int B);
int			handle_key(int key, void *param);
int			display_tri(t_game *game, t_form form);
int			display_circle(t_game *game, t_form circle, float thick);
int 		display_rec(t_game *game, t_form form, t_image **image);
int			display_map(t_game *game, t_image **image);
int			update_map(t_game *game);
int			display_full_range(t_game *game);
t_form		form(t_vector vector, t_vector dim, int color);
t_vector	vector(float x, float y);
t_vector	next_inter(t_vector p, t_vector vec, float teta, int *wall, t_game *game);
t_vector	next_hit(t_map *map, t_vector p, float teta, int *wall, t_game *game);
int			init_player(t_player *player);
t_vector	rotation_matrice(t_tex tex, t_game *game, int x, int y);
t_game		*init_game();
int			render(t_game *game);
int			centered_line(t_game *game, t_form form);
int			display_lifebar(t_game *game);
int			save_bitmap(t_game *game, char *name);
int			free_map(char **map, int counter);
#endif
