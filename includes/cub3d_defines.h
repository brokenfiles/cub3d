/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:31:25 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/16 15:34:59 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H
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

#endif