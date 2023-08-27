/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_files_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:19:26 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/26 20:39:50 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_tf	validate_files(t_parameters *parameters, char *file)
{
	int		fd;
	char	*temporary;
	char	**matrix;
	t_tf	bool;

	bool = TRUE;
	matrix = NULL;
	fd = open(file, O_RDONLY);
	temporary = get_next_line(fd);
	if (!temporary || fd == -1)
		return (FALSE);
	while (temporary && bool)
	{
		if (first_char_inval(fd, &temporary))
			break ;
		if (*temporary != '\n')
			bool = check_text(parameters, matrix, file, temporary);
		free(temporary);
		temporary = get_next_line(fd);
	}
	gnl_free(temporary, fd);
	if (bool)
		bool = validate_all_parameters(parameters);
	return (bool);
}

t_tf	first_char_inval(int fd, char **temporary)
{
	int	counter;

	counter = 0;
	if (*temporary == NULL)
		return (FALSE);
	while ((*temporary)[counter] == ' ' || (*temporary)[counter] == '\t')
		++counter;
	if (in_group((*temporary)[counter], VALID_ID) == FALSE)
	{
		free(*temporary);
		*temporary = get_next_line(fd);
		return (TRUE);
	}
	return (FALSE);
}

t_tf	check_text(t_parameters *params, char **text, char *file, char *temp)
{
	t_tf	bool;

	bool = FALSE;
	text = ft_split(temp, ' ');
	text[1] = arrange_colours(text);
	if (!ft_strncmp(text[0], "NO", 2) && ft_strlen(text[0]) == 2)
		bool = texture_validation(text[1], &params->north);
	else if (!ft_strncmp(text[0], "SO", 2) && ft_strlen(text[0]) == 2)
		bool = texture_validation(text[1], &params->south);
	else if (!ft_strncmp(text[0], "EA", 2) && ft_strlen(text[0]) == 2)
		bool = texture_validation(text[1], &params->east);
	else if (!ft_strncmp(text[0], "WE", 2) && ft_strlen(text[0]) == 2)
		bool = texture_validation(text[1], &params->west);
	else if (!ft_strncmp(text[0], "F", 1) && ft_strlen(text[0]) == 1)
		bool = colours_validation(text[1], &params->bottom_color);
	else if (!ft_strncmp(text[0], "C", 1) && ft_strlen(text[0]) == 1)
		bool = colours_validation(text[1], &params->top_color);
	else
		printf(E_ID_INVALID, file, text[0]);
	free_ptr_matrix(text);
	return (bool);
}

char	*arrange_colours(char **text)
{
	int		counter;
	char	*ret_string;
	char	*temporary;

	counter = -1;
	while (text[++counter])
	{
		continue ;
	}
	if (counter < 2 || !ft_strchr(text[1], ','))
	{
		return (text[1]);
	}
	counter = 1;
	ret_string = ft_strdup(text[1]);
	while (text[++counter])
	{
		temporary = ret_string;
		ret_string = ft_strjoin(ret_string, text[counter]);
		free(temporary);
	}
	free(text[1]);
	return (ret_string);
}

t_tf	colours_validation(char *colour_text, int *holder)
{
	char	**colour;
	char	*temporary;
	int		counter;
	t_tf	boolean;

	boolean = TRUE;
	if (commas_quantity(colour_text) != 2)
		return (print_error(E_COLOURS_QUANTITY));
	if (*holder != -1)
		return (print_error(E_COLOUR_DUPLICATED));
	temporary = text_string_erase(colour_text, " \n");
	colour = ft_split(temporary, ',');
	counter = -1;
	while (colour[++counter])
		if (ft_atoi(colour[counter]) > 255 || ft_atoi(colour[counter]) < 0)
			boolean = print_error(E_COLOUR_RANGE);
	if (counter != 3)
		boolean = print_error(E_COLOURS_QUANTITY);
	if (boolean)
		*holder = colour_get(ft_atoi(colour[0]), ft_atoi(colour[1]), \
					ft_atoi(colour[2]));
	free(temporary);
	free_ptr_matrix(colour);
	return (boolean);
}
