/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:48:32 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/16 22:38:19 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_tf	fail_validation(t_parameters *parameters, char **map)
{
	free_ptr_matrix(map);
	free(parameters->north);
	free(parameters->south);
	free(parameters->west);
	free(parameters->east);
	return (FALSE);
}

void	free_ptr_matrix(char **ptr_matrix)
{
	int	counter;

	counter = -1;
	if (!ptr_matrix)
		return ;
	while (ptr_matrix[++counter])
		free_pointer((void *)&ptr_matrix[counter]);
	free(ptr_matrix);
}

void	free_pointer(void **pointer)
{
	if (*pointer)
	{
		free(*pointer);
		*pointer = NULL;
	}
}

int	commas_quantity(char *string)
{
	int	counter;

	counter = 0;
	if (!string)
	{
		return (0);
	}
	while (*string)
	{
		if (*string == ',')
		{
			counter++;
		}
		string++;
	}
	return (counter);
}

void	gnl_free(char *temporary, int fd)
{
	if (fd == -1)
	{
		return ;
	}
	free(temporary);
	temporary = get_next_line(fd);
	while (temporary)
	{
		free(temporary);
		temporary = get_next_line(fd);
	}
	close (fd);
}
