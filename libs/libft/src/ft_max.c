/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:21:34 by dbrandao          #+#    #+#             */
/*   Updated: 2023/02/08 13:22:13 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

double	ft_max_d(double x, double y)
{
	if (x > y)
		return (x);
	return (y);
}
