/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:38:54 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/17 19:02:14 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>

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
	fdf->mlx->data = (unsigned int *)mlx_get_data_addr(fdf->mlx->img_ptr, &fdf->mlx->bpp, &fdf->mlx->size_line, &fdf->mlx->endian);
	ft_printf("bpp = %d, size_line = %d, endian = %d\n", fdf->mlx->bpp, fdf->mlx->size_line, fdf->mlx->endian);
	while (lst)
	{
		ft_printf("Je dessine un point a ((%d * %d * 1) + 20 + (%d * 100) = %d\n", fdf->mlx->size_line, lst->y, lst->x * 100, (fdf->mlx->size_line * lst->y * 10) + 20 + (lst->x * 100));
		fdf->mlx->data[(fdf->mlx->size_line * lst->y * 1) + 20 + (lst->x * 100)] = mlx_get_color_value(fdf->mlx->mlx_ptr, lst->color);
		if (lst->next)
		{
			ft_printf("Je trace une ligne entre %d et %d\n", (fdf->mlx->size_line * lst->y * 1) + 20 + (lst->x * 100) + k, (fdf->mlx->size_line * lst->next->y * 1) + 20 + (lst->next->x * 100) );
			if (lst->y == lst->next->y)
			{
				while (((fdf->mlx->size_line * lst->y * 1) + 20 + (lst->x * 100)) + k <
				((fdf->mlx->size_line * lst->next->y * 1) + 20 + (lst->next->x * 100)))
				{
					ft_printf("Je dessine un point de ligne a la position: %d\n", (fdf->mlx->size_line * lst->y * 1) + 20 + (lst->x * 100) + k);
					fdf->mlx->data[(fdf->mlx->size_line * lst->y * 1) + 20 + (lst->x * 100) + k] = mlx_get_color_value(fdf->mlx->mlx_ptr, lst->color);
					k++;
				}
				k = 0;
			}
		}
		//if (lst->y == 1 && lst->next->y == 2)
		//	break ;
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
