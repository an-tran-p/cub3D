#include "cub3d.h"

#ifndef ERR_MSG_H
# define ERR_MSG_H

# define MSG_NO_ARG "Include one scene file as argument\n"
# define MSG_EMPTY_ARG "Specify a scene file with .cub extension\n"
# define MSG_WRONG_FILE_EXT "A scene file should have .cub extension\n"
# define MSG_PERM_DENIED "Permission denied: can't read the file\n"
# define MSG_NO_FILE "No file found at the provided path\n"
# define MSG_IS_DIR "The path is a directory. Please provide a scene file\n"
# define MSG_INVALIB_RGB_R "Invalid RGB: R is outside the range 0-255\n"
# define MSG_INVALIB_RGB_G "Invalid RGB: G is outside the range 0-255\n"
# define MSG_INVALIB_RGB_B "Invalid RGB: B is outside the range 0-255\n"
# define MSG_WRONG_TEXTURE_EXT "A texture file should have .png extension\n"
# define MSG_NO_ACCESS_TO_TEXTURE "Can't access texture file\n"
# define MSG_TEXTURE_MISSING "Missing some required texture paths\n"
# define MSG_COLOR_MISSING "Missing some required color data\n"

#endif