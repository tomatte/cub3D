/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_file_01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:40:21 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/17 22:52:18 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

char	**get_array_map(int fd)
{
	char	*line;
	char	*temporary;
	char	**map_ret;

	if (fd == -1)
		return (NULL);
	temporary = get_next_line(fd);
	while (in_group(*temporary, VALID_ID))
	{
		free(temporary);
		temporary = get_next_line(fd);
		if (!temporary)
			return (NULL);
	}
	line = ft_strdup("");
	while (temporary)
	{
		line = string_merge(line, temporary);
		temporary = get_next_line(fd);
	}
	map_ret = ft_split(line, '\n');
	map_ret = padding_map(map_ret, max_string_size(map_ret));
	close(fd);
	free(line);
	return (map_ret);
}

t_tf	in_group(char cha, char *group)
{
	if (!group)
	{
		return (FALSE);
	}
	while (*group)
	{
		if (cha == *group)
		{
			return (TRUE);
		}
		group++;
	}
	return (FALSE);
}

char	*string_merge(char *string1, char *string2)
{
	char	*string_holder;
	size_t	size;

	if (!string1 || !string2)
	{
		free_pointer((void *)&string1);
		free_pointer((void *)&string2);
		return (NULL);
	}
	size = ft_strlen(string1) + ft_strlen(string2) + 1;
	string_holder = (char *)malloc(sizeof(char) * size);
	if (!string_holder)
		return (NULL);
	ft_strlcpy(string_holder, string1, ft_strlen(string1) + 1);
	ft_strlcat(string_holder, string2, size);
	free_pointer((void *)&string1);
	free_pointer((void *)&string2);
	return (string_holder);
}

char	**padding_map(char **map_mtx, int size_max)
{
	int		size;
	int		counter;
	char	*temporary;

	counter = -1;
	while (map_mtx[++counter])
	{
		size = ft_strlen(map_mtx[counter]);
		if (size < size_max)
		{
			temporary = malloc(sizeof(char) * size_max + 1);
			ft_strlcpy(temporary, map_mtx[counter], size + 1);
			ft_memset(temporary + size, ' ', size_max - size);
			temporary[size_max] = '\0';
			free(map_mtx[counter]);
			map_mtx[counter] = temporary;
		}
	}
	return (map_mtx);
}

int	max_string_size(char **group)
{
	int	counter;
	int	size_max;
	int	size;

	size_max = 0;
	counter = -1;
	while (group[++counter])
	{
		size = ft_strlen(group[counter]);
		if (size > size_max)
		{
			size_max = size;
		}
	}
	return (size_max);
}
