/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:53:31 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/10 16:34:59 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:31:25 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/09 11:03:09 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H
# define MIN_WIDTH							500
# define MIN_HEIGHT							500
# define MAX_WIDTH							2560
# define MAX_HEIGHT							1400
# define NORTH								90
# define EAST								0
# define WEST								180
# define SOUTH								270
# define MAX_ROT_SPEED						90
# define MAP_SIZE							200
# define MINIMAP_PLAYER_COLOR				0xA896FF
# define AIM_HEIGHT							25
# define AIM_WIDTH							1
# define AIM_CIRCLE_THICK					1
# define AIM_CIRCLE_COLOR					0xDC4A44
# define AIM_CIRCLE_SIZE					7
# define AIM_COLOR							0xFFFFFF
# define WALL_COLOR							0x474347
# define VOID_COLOR							0xFFFFFF
# define P_COLOR							0x4749FF
# define MAP_ONLY							"WENS0123LDHCU"
# define POS_ONLY							"WENS"
# define GAME_NAME							"cub3d"
# define ARGUMENT_SAVE						"-save"
# define ARGUMENT_DISABLE_MAP				"--disable-map"
# define MSG_MAP_ERROR						"Invalid map."
# define MSG_MAPNAME_ERROR					"Invalid map name."
# define MSG_RENDERING_ERROR				"Rendering error."
# define MSG_RENDERING_ERROR_428			"Rendering error. (ERROR_CODE 428)"
# define MSG_RENDERING_ERROR_429			"Rendering error. (ERROR_CODE 429)"
# define MSG_TOO_FEW_ARGUMENTS	"Too few arguments.\nUsage: ./cub3d <valid map>"
# define MSG_CANNOT_ALLOCATE_GAME_ERROR		"Cannot allocate global game."
# define MSG_CANNOT_ALLOCATE_MAP_ERROR		"Cannot allocate map."
# define MSG_CANNOT_ALLOCATE_IMAGE_ERROR	"Cannot allocate image."
# define MSG_CANNOT_ALLOCATE_PLAYER_ERROR	"Cannot allocate player."
# define MSG_CANNOT_INIT_MLX_ERROR			"Cannot init MLX."
# define MSG_CANNOT_INIT_MLX_WINDOW_ERROR	"Cannot init MLX's window."

#endif
