/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:38:54 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/25 17:40:56 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>
#include <math.h>

int		change_vue(t_fdf *fdf)
{
	if (fdf->map->vue == 0)
		fdf->map->vue = 1;
	else if (fdf->map->vue == 1)
		fdf->map->vue = 0;
	draw(fdf);
	return (0);
}

/*
** Fill pixel at the right position
*/

int		fill_pixel(t_fdf *fdf, int color, int y, int x)
{
	ft_printf("{y:%d x:%d}\n", y, x);
	int form = ((WIN_WIDTH * y) + x) * fdf->map->zoom_level + (WIN_WIDTH / 2);
	fdf->mlx->data[form] = mlx_get_color_value(fdf->mlx->mlx_ptr, color);
	return (0);
}

/*
** Make segment using Bresenham algorythm
*/

int		draw_line(t_fdf *fdf, int x1, int y1, int x2, int y2)
{
	int dx;
	int dy;
	int e;

	e = x2 - x1;
	dx = e * 2;
	dy = (y2 - y1) * 2;
	while (x1 <= x2)
	{
		fill_pixel(fdf, 0x00FFFFFF, x1, y1);
		x1++;
		if ((e = e - dy) <= 0)
		{
			y1++;
			e += dx;
		}
	}
	return (0);
}

/*
** Transform coordonates from 2d into ismetric vue
*/

t_map_lst	coords_to_iso(t_map_lst *elem)
{
	t_map_lst iso;
	int px;
	int py;

	//ft_printf("Before {y:%d x:%d}\n", elem->y, elem->x);
	px = elem->x;
	py = elem->y;
	iso.x = (px - py) * cos(0.523599);
	iso.y = - elem->alt + (px + py) * sin(0.523599);
	//ft_printf("After {y:%d x:%d}\n", elem->y, elem->x);
	return (iso);
}

/*
** Create new image and set it ready to draw
*/

int		set_image(t_fdf *fdf)
{
	t_map_lst	*lst;
	t_map_lst	iso;

	lst = fdf->map->lst;
	fdf->mlx->img_ptr = mlx_new_image(fdf->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->mlx->data = (unsigned int *)mlx_get_data_addr(fdf->mlx->img_ptr, &fdf->mlx->bpp, &fdf->mlx->size_line, &fdf->mlx->endian);
	//draw_line(fdf, 10, 10, 50, 30);
	while (lst)
	{
		if (fdf->map->vue == 1)
			fill_pixel(fdf, lst->color, lst->y, lst->x);
		else if (!fdf->map->vue)
		{
			iso = coords_to_iso(lst);
			fill_pixel(fdf, lst->color, iso.y, iso.x);
		}
		//if (lst && lst->next)
		//	draw_line(fdf, lst->x, lst->y, lst->next->x, lst->next->y);
		lst = lst->next;
	}
	mlx_put_image_to_window(fdf->mlx->mlx_ptr, fdf->mlx->mlx_win, fdf->mlx->img_ptr, 0, 50);
	mlx_loop(fdf->mlx->mlx_ptr);
	return (0);
}

/*
** Handle image creation and drawing
*/

int		draw(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx->mlx_ptr, fdf->mlx->mlx_win);
	set_image(fdf);
	//mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->data);
	return (0);
}
