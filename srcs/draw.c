/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:38:54 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/24 19:15:49 by lubenard         ###   ########.fr       */
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
	return (NULL);
}

/*
** Create new image and set it ready to draw
*/

int		set_image(t_fdf *fdf)
{
	int			k;
	t_map_lst	*lst;
	int			i;
	int			j;

	k = 0;
	i = 0;
	j = 0;
	lst = fdf->map->lst;
	fdf->mlx->img_ptr = mlx_new_image(fdf->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->mlx->data = malloc(sizeof(unsigned char) * 8294400);
	fdf->mlx->data = (unsigned int *)mlx_get_data_addr(fdf->mlx->img_ptr, &fdf->mlx->bpp, &fdf->mlx->size_line, &fdf->mlx->endian);
	ft_bzero(fdf->mlx->data, 8294400);
	while (lst)
	{
		coords_to_iso(lst);
		fill_pixel(fdf->mlx, lst->color, lst->y, lst->x);
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
