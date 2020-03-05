/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:56:51 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/04 12:45:56 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
/*
** Vue:
** 0: iso
** 1: flat
*/

int		change_vue(t_fdf *fdf)
{
	if (fdf->map->vue == 0)
		fdf->map->vue = 1;
	else if (fdf->map->vue == 1)
		fdf->map->vue = 0;
	mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->img_ptr);
	draw(fdf);
	return (0);
}

/*
** Zoom and dezoom on keypress
*/

int		zoom(t_fdf *fdf, int index)
{
	fdf->map->zoom_level += index;
	mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->img_ptr);
	draw(fdf);
	return (0);
}

/*
** Change altitude of points if they are != 0
*/

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
mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->img_ptr);
	draw(fdf);
	return (0);
}

/*
** Move the image on x axe
*/

int		move_x(t_fdf *fdf, int index)
{
	t_map_lst *map_tmp;

	map_tmp = fdf->map->lst;
	while (map_tmp)
	{
		map_tmp->x += index;
		map_tmp = map_tmp->next;
	}
mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->img_ptr);
	draw(fdf);
	return (0);
}

/*
** Move the image on y axe
*/

int		move_y(t_fdf *fdf, int index)
{
	t_map_lst *map_tmp;

	map_tmp = fdf->map->lst;
	while (map_tmp)
	{
		map_tmp->y += index;
		if (!fdf->map->vue)
			map_tmp->x += index;
		map_tmp = map_tmp->next;
	}
mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->img_ptr);
	draw(fdf);
	return (0);
}
