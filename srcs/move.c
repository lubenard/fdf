/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:56:51 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/25 17:43:38 by lubenard         ###   ########.fr       */
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
		map_tmp->alt += index;
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
		map_tmp->x += index;
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
		map_tmp->y += index;
		map_tmp = map_tmp->next;
	}
	draw(fdf);
	return (0);
}
