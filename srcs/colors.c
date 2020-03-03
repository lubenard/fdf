/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:05:08 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/03 14:44:04 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		change_colors(t_fdf *fdf)
{
	if (fdf->mlx->colors == 0)
		fdf->mlx->colors = 1;
	else if (fdf->mlx->colors == 1)
		fdf->mlx->colors = 0;
	draw(fdf);
	return (0);
}

int		colors(t_map_lst *lst, t_map_lst *lst_next, int colors)
{
	if (colors)
	{
		if (lst->alt >= 100 && lst_next->alt >= 100)
			return (0x00FF0000);
		else if (lst->alt <= 0 && lst_next->alt <= 0)
			return (0x000000FF);
		else if (lst->alt > 0 && lst_next->alt < 100)
			return (0x00228B22);
		else
			return (0x007FFFD4);
	}
	return (0x00FFFFFF);
}
