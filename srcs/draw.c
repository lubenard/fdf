/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:38:54 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/13 17:40:08 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>

/*
** Create new image and set it ready to draw
*/

int		init_image(t_fdf *fdf)
{
	mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);

	return (0);
}

/*
** Handle image creation and drawing
*/
int		draw(t_fdf *fdf)
{
	init_image(fdf);
	return (0);
}
