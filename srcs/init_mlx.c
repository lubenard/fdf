/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:58:55 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/05 13:35:21 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"

/*
** Keycodes (MacOS):
** 126: key up
** 125: key down
** 123: key left
** 124: key right
** 15:  key r (change colors)
** 69:  key + (zoom in)
** 78:  key - (zoom out)
** 53:  key escape (quit)
** 9:   key v (change vue)
** 27:  key shift + '-' (decrease relief)
** 24:  key shift + '=' (increase relief)
**
** Keycode (Unix systems)
** 65362 : key up
** 65364 : key down
** 65361 : key left
** 65363 : key right
** 114   :  key r (change colors)
** 65451 :  key + (zoom in)
** 65453 :  key - (zoom out)
** 65307 :  key escape (quit)
** 118   :  key v (change vue)
** 97    :  key a (decrease relief)
** 101   :  key e (increase relief)
*/

int		keys(int keycode, void *param)
{
	if (keycode == 53 || keycode == 65307)
		quit_fdf((t_fdf *)param);
	else if (keycode == 126 || keycode == 65362)
		move_y((t_fdf *)param, -2);
	else if (keycode == 125 || keycode == 65364)
		move_y((t_fdf *)param, 2);
	else if (keycode == 123 || keycode == 65361)
		move_x((t_fdf *)param, -2);
	else if (keycode == 124 || keycode == 65363)
		move_x((t_fdf *)param, 2);
	else if (keycode == 69 || keycode == 65451)
		zoom((t_fdf *)param, 2);
	else if (keycode == 78 || keycode == 65453)
		zoom((t_fdf *)param, -2);
	else if (keycode == 24 || keycode == 101)
		change_alt((t_fdf *)param, 1);
	else if (keycode == 27 || keycode == 97)
		change_alt((t_fdf *)param, -1);
	else if (keycode == 9 || keycode == 118)
		change_vue((t_fdf *)param);
	else if (keycode == 15 || keycode == 114)
		change_colors((t_fdf *)param);
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
	fdf->mlx->img_ptr = mlx_new_image(fdf->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->mlx->data = (unsigned int *)mlx_get_data_addr(fdf->mlx->img_ptr,
	&fdf->mlx->bpp, &fdf->mlx->size_line, &fdf->mlx->endian);
	return (0);
}
