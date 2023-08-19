/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_05.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felcaue- <felcaue-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 00:53:04 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/19 01:16:46 by felcaue-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_tf	geom_inner_sealed(char **map_array)
{
	char	*edge_inner;
	int		counter;

	counter = -1;
	while (map_array[++counter])
	{
		edge_inner = ft_strchr(map_array[counter], OUTLINE);
		if (edge_inner)
		{
			if (geom_crawl(map_array, counter, edge_inner - \
					map_array[counter], INNER_EDGE) == FALSE)
			{
				return (FALSE);
			}
			counter--;
		}
	}
	return (TRUE);
}
