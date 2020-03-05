/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:38:54 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/05 13:35:48 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>
#include <math.h>

/*
** Fill pixel at the right position, gave by x and y
** The "write", line 10 might seems useless, but make version under arch linux
** working
*/

int		fill_pixel(t_fdf *fdf, int color, int y, int x)
{
	int form;

	form = (((WIN_WIDTH * y) + x));
	if (x > 0 && y > 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		write(1, "", 1);
		fdf->mlx->data[form] = mlx_get_color_value(fdf->mlx->mlx_ptr, color);
	}
	return (0);
}

/*
** Transform coordonates from 2d into ismetric vue
*/

t_point	coords_to_iso(t_map *map, t_map_lst *elem, int vue)
{
	t_map_lst	iso;
	int			px;
	int			py;
	int			pz;

	px = elem->x * map->zoom_level;
	py = elem->y * map->zoom_level;
	pz = map->zoom_level;
	if (!vue)
	{
		iso.y = -elem->alt * elem->manual_alt + (px + py) * sin(0.523599);
		iso.x = (px - py) * cos(0.523599);
	}
	else
	{
		iso.y = py;
		iso.alt = pz;
		iso.x = px;
	}
	iso.x += (WIN_WIDTH - (map->line_size * 4)) / 2;
	iso.y += (WIN_HEIGHT - (map->height_size * 4)) / 2;
	return (ft_ret_coord(iso));
}

/*
** Create new image and set it ready to draw
*/

int		set_image(t_fdf *fdf)
{
	t_map_lst	*lst;
	t_point		one;
	t_point		two;

	lst = fdf->map->lst;
	while (lst)
	{
		one = coords_to_iso(fdf->map, lst, fdf->map->vue);
		if (lst->next && lst->y == lst->next->y)
		{
			two = coords_to_iso(fdf->map, lst->next, fdf->map->vue);
			draw_line(fdf, one, two, colors(lst, lst->next, fdf->mlx->colors));
		}
		if (lst->down && lst->x == lst->down->x)
		{
			two = coords_to_iso(fdf->map, lst->down, fdf->map->vue);
			draw_line(fdf, one, two, colors(lst, lst->down, fdf->mlx->colors));
		}
		lst = lst->next;
	}
	mlx_put_image_to_window(fdf->mlx->mlx_ptr, fdf->mlx->mlx_win,
	fdf->mlx->img_ptr, 0, 0);
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
	mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->data);
	return (0);
}
