/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:20:05 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/05 08:01:43 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_min(int x, int y)
{
	if (x < y)
		return (x);
	return (y);
}

double	ft_min_d(double x, double y)
{
	if (x < y)
		return (x);
	return (y);
}
