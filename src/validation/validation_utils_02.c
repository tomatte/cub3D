/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:44:31 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/17 00:21:45 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	string_size(char *string, char *cha_group)
{
	int	counter;

	counter = 0;
	while (*string)
	{
		if (!char_trim(*string++, cha_group))
		{
			counter++;
		}
	}
	return (counter);
}

int	char_trim(char cha, char const *cha_group)
{
	while (*cha_group)
	{
		if (cha == *cha_group)
		{
			return (1);
		}
		cha_group++;
	}
	return (0);
}
