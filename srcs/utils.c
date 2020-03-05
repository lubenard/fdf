/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:40:47 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/04 11:16:00 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
/*
** Used to invert position and store them into t_point struct
*/

t_point	ft_ret_coord(t_map_lst iso)
{
	t_point point;

	point.x = iso.y;
	point.y = iso.x;
	point.alt = iso.alt;
	return (point);
}

/*
** Quit fdf, freeing everything. Triggered by ESC key
*/

void	quit_fdf(t_fdf *fdf)
{
	write(1, "Exiting Fdf...\n", 16);
	free_structs(fdf, 0);
	exit(0);
}

int		error(char *error_message)
{
	write(2, error_message, ft_strlen(error_message));
	return (1);
}

/*
** Free structs before exit or if problem is encountered
*/

int		free_structs(t_fdf *fdf, int return_code)
{
	t_map_lst	*tmp_lst;

	while (fdf->map->lst)
	{
		tmp_lst = fdf->map->lst;
		fdf->map->lst = fdf->map->lst->next;
		ft_memdel((void **)&tmp_lst);
	}
	mlx_destroy_window(fdf->mlx->mlx_ptr, fdf->mlx->mlx_win);
	mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->img_ptr);
	ft_memdel((void**)&fdf->map);
	ft_memdel(&fdf->mlx->mlx_ptr);
	ft_memdel((void**)&fdf->mlx);
	ft_memdel((void**)&fdf);
	return (return_code);
}
