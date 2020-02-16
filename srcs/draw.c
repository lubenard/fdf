/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:38:54 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/16 16:08:46 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>

//int		pixel_put(int color, int y, int x)

/*
** Create new image and set it ready to draw
*/

int		set_image(t_fdf *fdf)
{
	void	*img_ptr;
	int		bpp;
	int		size_line;
	int		endian;
	unsigned int *data;
	int k = 0;

	img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data = (unsigned int *)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	ft_printf("bpp = %d, size_line = %d, endian = %d\n", bpp, size_line, endian);
	while (k != 100)
	{
		if (k % 2 == 0)
		{
			data[k] = mlx_get_color_value(fdf->mlx_ptr, 0x00FFFFFF);
			data[100 * size_line + k] =  mlx_get_color_value(fdf->mlx_ptr, 0x00FFFFFF);
		}
		k++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->mlx_win, img_ptr, 0, 50);
	//mlx_destroy_image(fdf->mlx_ptr, data);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}

/*
** Handle image creation and drawing
*/

int		draw(t_fdf *fdf)
{
	set_image(fdf);
	return (0);
}
