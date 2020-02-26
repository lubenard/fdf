/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:38:54 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/26 16:34:52 by lubenard         ###   ########.fr       */
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
	(void)color;
	ft_printf("{y:%d x:%d},\n", y, x);
	//int form = ((WIN_WIDTH * y) + x) * fdf->map->zoom_level + (WIN_WIDTH / 2);
	int form = (((WIN_WIDTH * y) + x) * fdf->map->zoom_level);
	if (x > 0 && y > 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		fdf->mlx->data[form] = mlx_get_color_value(fdf->mlx->mlx_ptr, color);
	}
	return (0);
}

/*
** Make segment using Bresenham algorythm
*/

void	draw_line3(t_fdf *fdf, int x1, int y1, int x2, int y2)
{
	int dy;
	int sy;
	int dx;
	int sx;

	if (x1 == x2 && y1 == y2)
	{
		fill_pixel(fdf, 0x00FFFFFF, x1, y1);
		return ;
	}
	dx = x1 - x2;
	sx = (dx < 0) ? -1 : 1;
	dy = y1 - y2;
	sy = (dy < 0) ? -1 : 1;
	if (abs(dy) < abs(dx))
	{
		int m = dy / dx;
		int b = y1 - m * x1;
		while (x1 != x2)
		{
			ft_printf("looping here, x1 = %d and x2 = %d\n", x1, x2);
			fill_pixel(fdf, 0x00FFFFFF, x1, m * x1 + b);
			x1 += sx;
		}
	}
	else
	{
		int m = dx / dy;
		int b = x1 - m * y1;
		while (y1 != y2)
		{
			ft_printf("looping here TOO, y1 = %d and y2 = %d sy = %d\n", y1, y2, sy);
			fill_pixel(fdf, 0x00FFFFFF, m * y1 + b, y1);
			y1 += sy;
		}
	}
}

void	draw_line2(t_fdf *fdf, int x1, int y1, int x2, int y2)
{
	int  x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

	dx = x2 - x1;
	dy = y2 - y1;

	dx1 = abs(dx);
	dy1 = abs(dy);

	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;

	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1; y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}
		fill_pixel(fdf, 0x00FFFFFF, x, y);
		for (i = 0; x < xe; i++) {
			x = x + 1;
			if (px < 0) {
				px = px + 2 * dy1;
			} else {
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
					y = y + 1;
				} else {
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			fill_pixel(fdf, 0x00FFFFFF, x, y);
		}
	} else {
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}
		fill_pixel(fdf, 0x00FFFFFF, x, y);
		for (i = 0; y < ye; i++) {
			y = y + 1;
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx < 0 && dy<0) || (dx > 0 && dy > 0)) {
					x = x + 1;
				} else {
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			fill_pixel(fdf, 0x00FFFFFF, x, y);
		}
	}
}

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
	iso.y = - elem->alt + elem->manual_alt + (px + py) * sin(0.523599);
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
	draw_line3(fdf, 60, 30, 50, 10);
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
	mlx_put_image_to_window(fdf->mlx->mlx_ptr, fdf->mlx->mlx_win, fdf->mlx->img_ptr, 0, 0);
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
