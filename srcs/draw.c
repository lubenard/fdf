/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:38:54 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/27 18:40:52 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>
#include <math.h>

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
	draw(fdf);
	return (0);
}

/*
** Fill pixel at the right position, gave by x and y
*/

int		fill_pixel(t_fdf *fdf, int color, int y, int x)
{
	//ft_printf("{y:%d x:%d},\n", y, x);
	//int form = ((WIN_WIDTH * y) + x) * fdf->map->zoom_level + (WIN_WIDTH / 2);
	int form = (((WIN_WIDTH * y) + x));// * fdf->map->zoom_level);
	if (x > 0 && y > 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
		fdf->mlx->data[form] = mlx_get_color_value(fdf->mlx->mlx_ptr, color);
	return (0);
}

/*
** Make segment using Bresenham algorythm
*/

typedef struct	s_point
{
	double x;
	double y;
	double z;
}				t_point;

void	drawline_init(t_point *delta, t_point *s, t_point one, t_point two)
{
	delta->x = two.x - one.x;
	s->x = (delta->x < 0) ? -1 : 1;
	delta->y = two.y - one.y;
	s->y = (delta->y < 0) ? -1 : 1;
}

void	draw_line2(t_fdf *ptr, t_point one, t_point two, int color)
{
	t_point	delta;
	t_point	s;
	double	slope;
	double	pitch;

	//ft_printf("je trace une ligne entre {%f, %f} et {%f, %f}\n", one.y, one.x, two.y, two.x);
	drawline_init(&delta, &s, one, two);
	slope = (fabs(delta.y) < fabs(delta.x)) ? delta.y / delta.x
		: delta.x / delta.y;
	pitch = (fabs(delta.y) < fabs(delta.x)) ? one.y - (slope * one.x)
		: one.x - (slope * one.y);
	if (fabs(delta.y) < fabs(delta.x))
		while ((int)round(one.x) != (int)round(two.x))
		{
			fill_pixel(ptr, color, (int)round(one.x),
					(int)lround((slope * one.x) + pitch));
			one.x += s.x;
		}
	else
		while ((int)round(one.y) != (int)round(two.y))
		{
			fill_pixel(ptr, color, (int)lround((slope * one.y) + pitch),
					(int)round(one.y));
			one.y += s.y;
		}
}

/*
** Transform coordonates from 2d into ismetric vue
*/

t_map_lst	coords_to_iso(t_map *map, t_map_lst *elem, int vue)
{
	t_map_lst iso;
	int px;
	int py;
	int pz;
	double x1;
	double y1;

	px = elem->x * map->zoom_level;
	py = elem->y * map->zoom_level;
	pz = map->zoom_level * 1;
	if (vue == 0)
	{
		//iso.x = (px - py) * cos(0.523599);
		//iso.y = - elem->alt + elem->manual_alt + (px + py) * sin(0.523599);
		x1 = (px - py) * cos(0.523599);
		y1 = - elem->alt + elem->manual_alt + (px + py) * sin(0.523599);
		iso.y = y1;
		iso.x = x1;
	}
	else
	{
		iso.y = (py * cos(0)) + (pz * sin(0));
		iso.alt = (pz * cos(0)) - (py * sin(0));
		iso.x = (px * cos(0)) + (iso.alt * sin(0));
		px = iso.x;
		iso.x = (iso.x * cos(0)) - (iso.y * sin(0));
		iso.y = (px * sin(0)) + (iso.y * cos(0));
	}
	iso.x += (WIN_WIDTH - (map->line_size * 4)) / 2;
	iso.y += (WIN_HEIGHT - (map->height_size * 4)) / 2;
	//ft_printf("Converted point {y:%d x:%d}\n",iso.y , iso.x);
	return (iso);
}

/*
** Create new image and set it ready to draw
*/

int		set_image(t_fdf *fdf)
{
	t_map_lst	*lst;
	t_map_lst	iso;
	t_map_lst iso2;
	t_point one;
	t_point two;

	lst = fdf->map->lst;
	fdf->mlx->img_ptr = mlx_new_image(fdf->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->mlx->data = (unsigned int *)mlx_get_data_addr(fdf->mlx->img_ptr, &fdf->mlx->bpp, &fdf->mlx->size_line, &fdf->mlx->endian);
	one.y = 502.0;
	one.x = 340.0;
	one.z = 0;
	two.y = 506.0;
	two.x = 340.0;
	two.z = 0;
	draw_line2(fdf, one, two, 0x00FFFFFF);
	while (lst)
	{
		if (fdf->map->vue == 1)
		{
			iso = coords_to_iso(fdf->map, lst, fdf->map->vue);
			one.x = iso.y;
			one.y = iso.x;
			one.z = iso.alt;
			if (lst->next && lst->y == lst->next->y)
			{
				iso2 = coords_to_iso(fdf->map, lst->next, fdf->map->vue);
				two.x = iso2.y;
				two.y = iso2.x;
				two.z = iso2.alt;
				draw_line2(fdf, one , two, 0x00FFFFFF);
			}
			if (lst->down && lst->x == lst->down->x)
			{
				//ft_printf("Je rentre ici\n");
				iso2 = coords_to_iso(fdf->map, lst->down, fdf->map->vue);
				two.x = iso2.y;
				two.y = iso2.x;
				two.z = iso2.alt;
				draw_line2(fdf, one , two, 0x00FFFFFF);
			}
			//ft_printf("Je Put pixel a {%d, %d}\n", iso.y, iso.x);
			fill_pixel(fdf, lst->color, iso.y, iso.x);
		}
		else if (!fdf->map->vue)
		{
			iso = coords_to_iso(fdf->map, lst, fdf->map->vue);
			one.x = iso.y;
			one.y = iso.x;
			one.z = iso.alt;
			//ft_printf("Je Put pixel a {%d, %d}\n", iso.y, iso.x);
			if (lst->next && lst->y == lst->next->y)
			{
				iso2 = coords_to_iso(fdf->map, lst->next, fdf->map->vue);
				two.x = iso2.y;
				two.y = iso2.x;
				two.z = iso2.alt;
				draw_line2(fdf, one , two, 0x00FFFFFF);
			}
			if (lst->down && lst->x == lst->down->x)
			{
				//ft_printf("Je rentre ici\n");
				iso2 = coords_to_iso(fdf->map, lst->down, fdf->map->vue);
				two.x = iso2.y;
				two.y = iso2.x;
				two.z = iso2.alt;
				draw_line2(fdf, one , two, 0x00FFFFFF);
			}
			fill_pixel(fdf, lst->color, iso.y, iso.x);
		}
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
