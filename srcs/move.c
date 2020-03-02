/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:56:51 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/02 17:23:58 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		zoom(t_fdf *fdf, int index)
{
	fdf->map->zoom_level += index;
	draw(fdf);
	return (0);
}

int		change_alt(t_fdf *fdf, int index)
{
	t_map_lst *map_tmp;

	map_tmp = fdf->map->lst;
	while (map_tmp)
	{
		if (map_tmp->alt != 0)
			map_tmp->manual_alt += index;
		map_tmp = map_tmp->next;
	}
	draw(fdf);
	return (0);
}

int		move_x(t_fdf *fdf, int index)
{
	t_map_lst *map_tmp;

	map_tmp = fdf->map->lst;
	while (map_tmp)
	{
		map_tmp->x += (fdf->map->zoom_level) ?
			index * (fdf->map->zoom_level * 2) : index;
		map_tmp = map_tmp->next;
	}
	draw(fdf);
	return (0);
}

int		move_y(t_fdf *fdf, int index)
{
	t_map_lst *map_tmp;

	map_tmp = fdf->map->lst;
	while (map_tmp)
	{
		map_tmp->y += (fdf->map->zoom_level) ?
			index * (fdf->map->zoom_level * 2) : index;
		map_tmp = map_tmp->next;
	}
	draw(fdf);
	return (0);
}
