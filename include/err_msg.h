/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:50:18 by ikozhina          #+#    #+#             */
/*   Updated: 2025/10/02 09:56:36 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_MSG_H
# define ERR_MSG_H

# define MSG_NO_ARG "Include one scene file as argument\n"
# define MSG_EMPTY_ARG "Specify a scene file with .cub extension\n"
# define MSG_WRONG_FILE_EXT "A scene file should have .cub extension\n"
# define MSG_PERM_DENIED "Permission denied: can't read the file\n"
# define MSG_NO_FILE "No file found at the provided path\n"
# define MSG_IS_DIR "The path is a directory. Please provide a scene file\n"
# define MSG_INVALID_RGB_R "Invalid RGB: R is outside the range 0-255\n"
# define MSG_INVALID_RGB_G "Invalid RGB: G is outside the range 0-255\n"
# define MSG_INVALID_RGB_B "Invalid RGB: B is outside the range 0-255\n"
# define MSG_WRONG_TEXTURE_EXT "A texture file should have .png extension\n"
# define MSG_NO_ACCESS_TO_TEXTURE "Can't access texture file\n"
# define MSG_MISSING_NO "Missing North texture (NO)\n"
# define MSG_MISSING_SO "Missing South texture (SO)\n"
# define MSG_MISSING_WE "Missing West texture (WE)\n"
# define MSG_MISSING_EA "Missing East texture (EA)\n"
# define MSG_MISSING_F "Missing floor color (F)\n"
# define MSG_MISSING_C "Missing ceiling color (C)\n"
# define MSG_TOO_MANY_PLAYERS "Only one player start position allowed\n"
# define MSG_NO_PLAYER "Player start position required\n"
# define MSG_NO_WALL "The map must be closed by walls\n"
# define MSG_EMPTY_LINES "Empty lines inside the map are not allowed\n"
# define MSG_EMPTY_SPACES "Spaces inside the map must be closed by walls\n"
# define MSG_DUP_TEXTURE "Duplicate texture path\n"

#endif