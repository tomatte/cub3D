/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:56:37 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/05 16:07:47 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGE_H
# define ERROR_MESSAGE_H

# define E_NO_MAP "Error\nMap file name was not specified\nusage: ./cub3d <map file name>\n"
# define E_MORE_MAP "Error\nMultiple map files provided in command\nusage: ./cub3d <map file name>\n"
# define E_MAP_EXTENSION "Error\nIncorrect map file extension\nExpected: <map name>.cub\n"
# define E_MAP_INVALID "Error\nMap file does not exist or has incorrect permissions\n"
# define E_MAP_NAME_INVALID "Error\nMap file name invalid: %s\n"
# define E_MAP_CHARS_INVALID "Error\nInvalid characters in the map file\n"
# define E_MAP_WALLS_OUTER "Error\nThe outer walls of the map are open\n"
# define E_MAP_WALLS_INNER "Error\nThe inner walls of the map are open"
# define E_MAP_EMPTY "Error\nThe map file is empty\n"

# define E_MORE_PLAYERS "Error\nIncorrect number of specific characters in the map\n"

# define E_NO_TEXTURES "Error\nMissing texture file\n"
# define E_TEXTURE_DUPLICATED "Error\nDuplicate texture file"
# define E_TEXTURE_EXTENSION "Error\nIncorrect file type\nExpected: .xpm\n"
# define E_TEXTURE_INVALID "Error\nTexture file does not exist or has incorrect permissions\n"

# define E_NO_COLOUR "Error\nMissing colour\n"
# define E_COLOUR_RANGE "Error\nColour value not in range\n"
# define E_COLOURS_QUANTITY "Error\nWrong number of colours in set\n"
# define E_COLOUR_DUPLICATED "Error\nDuplicate colour ID\n"

# define E_ID_INVALID "Error\n%s: Invalid ID: %s\n"
# define E_WINDOW_SIZE_INVALID "Error\nWindow size below 1024x768\n"

#endif