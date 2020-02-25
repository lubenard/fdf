/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:58:55 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/25 14:32:16 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "fdf.h"

/*
** Keycodes:
** 126: key up
** 125: key down
** 123: key left
** 124: key right
** 69:  key + (zoom in)
** 78:  key - (zoom out)
** 53:  key escape (quit)
*/

int		keys(int keycode, void *param)
{
	if (keycode == 53)
		quit_fdf((t_fdf *)param);
	else if (keycode == 126)
		move_y((t_fdf *)param, -1);
	else if (keycode == 125)
		move_y((t_fdf *)param, 1);
	else if (keycode == 123)
		move_x((t_fdf *)param, -1);
	else if (keycode == 124)
		move_x((t_fdf *)param, 1);
	else if (keycode == 69)
		zoom((t_fdf *)param, 1);
	else if (keycode == 78)
		zoom((t_fdf *)param, -1);
	return (0);
}

/*
** Init windows
*/

int		init_mlx(t_fdf *fdf)
{
	if (!(fdf->mlx->mlx_ptr = mlx_init()))
		return (1);
	fdf->mlx->mlx_win = mlx_new_window(fdf->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
	"Fil de fer (aka fdf)");
	mlx_key_hook(fdf->mlx->mlx_win, keys, fdf);
	return (0);
}
