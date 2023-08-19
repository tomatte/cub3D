/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_files_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:08:48 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/16 23:18:53 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	colour_get(int red, int green, int blue)
{
	int	colour;

	colour = 0;
	colour += (red & 0xFF) << 16;
	colour += (green & 0XFF) << 8;
	colour += (blue & 0XFF);
	return (colour);
}

char	*text_string_erase(char *string, char *group)
{
	size_t	length;
	char	*result;

	if (!string)
	{
		return (NULL);
	}
	length = strsize(string, group);
	result = (char *)malloc(sizeof(char) * length + 1);
	while (*string)
	{
		if (!istrimmed(*string, group))
		{
			*result++ = *string++;
		}
		else
		{
			string++;
		}
	}
	*result = '\0';
	return (result - length);
}

t_tf	texture_validation(char *file_holder, char **holder_res)
{
	int		fd;
	char	*holder_dot;

	if (*holder_res)
		return (print_error(E_TEXTURE_DUPLICATED));
	if (!file_holder)
	{
		return (FALSE);
	}
	holder_dot = ft_strrchr(file_holder, '.');
	if (!holder_dot || ft_strncmp(holder_dot, ".xpm\n", 5))
	{
		printf("%sgot: %s\n", E_TEXTURE_EXTENSION, file_holder);
		return (FALSE);
	}
	file_holder[ft_strlen(file_holder) - 1] = '\0';
	fd = open(file_holder, O_RDONLY);
	if (fd == -1)
	{
		printf("%s%s\n", E_TEXTURE_INVALID, file_holder);
		return (FALSE);
	}
	close(fd);
	*holder_res = ft_strdup(file_holder);
	return (TRUE);
}

t_tf	validate_all_parameters(t_parameters *parameters)
{
	if (parameters->north == NULL || parameters->east == NULL
		|| parameters->south == NULL || parameters->west == NULL)
	{
		return (print_error(E_NO_TEXTURES));
	}
	if (parameters->top_color == -1 || parameters->bottom_color == -1)
	{
		return (print_error(E_NO_COLOUR));
	}
	return (TRUE);
}
