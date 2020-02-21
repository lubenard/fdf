/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:38:54 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/21 16:32:22 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>
#include <math.h>

int		fill_pixel(t_mlx *mlx, int color, int y, int x)
{
	ft_printf("{y:%d x:%d}\n", y, x);

	int form = ((WIN_WIDTH * y) + x) * 6 + (WIN_WIDTH / 2);
	mlx->data[form] = mlx_get_color_value(mlx->mlx_ptr, color);
	return (0);
}

t_map_lst	*coords_to_iso(t_map_lst *elem)
{
	int px;
	int py;
	ft_printf("Before {y:%d x:%d}\n", elem->y, elem->x);
	px = elem->x;
	py = elem->y;
	elem->x = (px - py) * cos(0.523599);
	elem->y = - elem->alt + (px + py) * sin(0.523599);
	ft_printf("After {y:%d x:%d}\n", elem->y, elem->x);
	return (elem);
}

void	drawline_init(t_coord *delta, t_coord *s, t_map_lst *one, t_map_lst *two)
{
	delta->x = two->x - one->x;
	s->x = (delta->x < 0) ? -1 : 1;
	delta->y = two->y - one->y;
	s->y = (delta->y < 0) ? -1 : 1;
}

void	fdf_draw_line(t_mlx *mlx, t_map_lst *one, t_map_lst *two, int color)
{
	t_coord		delta;
	t_coord		s;
	double		slope;
	double		pitch;

	drawline_init(&delta, &s, one, two);
	slope = (fabs(delta.y) < fabs(delta.x)) ? delta.y / delta.x
		: delta.x / delta.y;
	pitch = (fabs(delta.y) < fabs(delta.x)) ? one->y - (slope * one->x)
		: one->x - (slope * one->y);
	if (fabs(delta.y) < fabs(delta.x))
		while ((int)round(one->x) != (int)round(two->x))
		{
			fill_pixel(mlx, (int)round(one->x),
					(int)lround((slope * one->x) + pitch), color);
			one->x += s.x;
		}
	else
		while ((int)round(one->y) != (int)round(two->y))
		{
			fill_pixel(mlx, (int)lround((slope * one->y) + pitch),
					(int)round(one->y), color);
			one->y += s.y;
		}
}

void	disp_join_points(t_mlx *mlx, t_map_lst *lst, int i, int j)
{
	int color;

	(void)i;
	(void)j;
	color = 0xFFFFFF;
	if (lst->next)
	{
		if (lst->alt > 0 && lst->next->alt > 0 && lst->y == lst->next->y)
			color = 0x4073ed;
		fdf_draw_line(mlx, coords_to_iso(lst),
			coords_to_iso(lst->next), color);
	}
	/*if (i + 1 < 10) //lines of the map
	{
		if (ptr->map[i][j] > 0 && ptr->map[i + 1][j] > 0)
			color = 0x4073ed;
		fdf_draw_line(mlx, fdf_coords(j, i, ptr->map[i][j], ptr),
			fdf_coords(j, i + 1, ptr->map[i + 1][j], ptr), color);
	}
	color = 0xFFFFFF;
	if (j + 1 < ptr->size_x)
	{
		if (ptr->map[i][j] > 0 && ptr->map[i][j + 1] > 0)
			color = 0x4073ed;
		fdf_draw_line(mlx, fdf_coords(j, i, ptr->map[i][j], ptr),
			fdf_coords(j + 1, i, ptr->map[i][j + 1], ptr), color);
	}*/
}


/*
** Create new image and set it ready to draw
*/

int		set_image(t_fdf *fdf)
{
	int			k;
	t_map_lst	*lst;

	k = 0;
	lst = fdf->map->lst;
	fdf->mlx->img_ptr = mlx_new_image(fdf->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->mlx->data = malloc(sizeof(unsigned char) * 8294400);
	fdf->mlx->data = (unsigned int *)mlx_get_data_addr(fdf->mlx->img_ptr, &fdf->mlx->bpp, &fdf->mlx->size_line, &fdf->mlx->endian);
	ft_bzero(fdf->mlx->data, 8294400);
	while (lst)
	{
		//coords_to_iso(lst);
		//fill_pixel(fdf->mlx, lst->color, lst->y, lst->x);
		disp_join_points(fdf->mlx, lst, 0, 0);
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
	set_image(fdf);
	//mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->data);
	return (0);
}
