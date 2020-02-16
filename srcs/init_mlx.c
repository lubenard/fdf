/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:58:55 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/16 16:36:26 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "fdf.h"

/*
** Init mlx + set escape touch as quit
*/

int		escape_key(int keycode, void *param)
{
	if (keycode == 53)
	{
		free_structs((t_fdf *)param);
		exit(0);
	}
	return (0);
}

int		init_mlx(t_fdf *fdf)
{
	ft_printf("fdf is %p and mlx_ptr %p\n", fdf, fdf->mlx_ptr);
	if (!(fdf->mlx_ptr = mlx_init()))
		return (1);
	fdf->mlx_win = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
	"Fil de fer (aka fdf)");
	mlx_key_hook(fdf->mlx_win, escape_key, fdf);
	//mlx_loop(fdf->mlx_ptr); //need to be set after image draw
	return (0);
}
