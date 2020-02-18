/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:38:54 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/18 13:45:58 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>

int		fill_pixel(t_mlx *mlx, int color, int y, int x, char *DEBUG)
{
	(void)DEBUG;
	ft_printf("Je dessine un point pour %s a ((%d * %d * 1) + 20 + (%d * 100) = %d\n", DEBUG , mlx->size_line, y, x * 100, (mlx->size_line * y * 5) + 20 + (x * 100));
	mlx->data[mlx->size_line * y + x] = mlx_get_color_value(mlx->mlx_ptr, color);
	return (0);
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
	fdf->mlx->data = (unsigned int *)mlx_get_data_addr(fdf->mlx->img_ptr, &fdf->mlx->bpp, &fdf->mlx->size_line, &fdf->mlx->endian);
	while (lst)
	{
		fill_pixel(fdf->mlx, lst->color, lst->y * 5 , lst->x * 100 + 20 + lst->alt * 3, "POINT");
		if (lst->next && lst->y == lst->next->y)
		{
			//ft_printf("Je trace une ligne entre %d et %d\n", (fdf->mlx->size_line * lst->y * 5) + 20 + (lst->x * 100) + k, (fdf->mlx->size_line * lst->next->y * 5) + 20 + (lst->next->x * 100) );
				while (fdf->mlx->size_line * lst->y * 5 + lst->x * 100 + 20 + lst->alt * 3 + k <
				fdf->mlx->size_line * lst->next->y * 5 + lst->next->x * 100 + 20 + lst->alt * 3)
					fill_pixel(fdf->mlx, lst->color, lst->y * 5, lst->x * 100 + 20 + lst->alt * 3 + k++, "LIGNE VERTICALE");
				k = 0;
		}
		k = 0;
		if (lst->up)
		{
			k = -5;
			//ft_printf("%d - %d = %d\n", fdf->mlx->size_line * lst->y * 5 + lst->x * 100 + 20,fdf->mlx->size_line * lst->up->y * 5 + lst->up->x * 100 + 20 , (fdf->mlx->size_line * lst->up->y * 5 + lst->up->x * 100 + 20) - (fdf->mlx->size_line * lst->y * 5 + lst->x * 100 + 20));
			while (k != 0)
			{
				fill_pixel(fdf->mlx, 0x00FFFFFF, lst->y * 5 + k, lst->x * 100 + 20 + lst->alt * 3, "LIGNE HORIZONTAL");
				k++;
			}
			k = 0;
		}
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
