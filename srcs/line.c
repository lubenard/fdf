/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:25:35 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/03 14:44:18 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*
** Make segment using Bresenham algorythm
*/

void	drawline_init(t_point *delta, t_point *s, t_point one, t_point two)
{
	delta->x = two.x - one.x;
	s->x = (delta->x < 0) ? -1 : 1;
	delta->y = two.y - one.y;
	s->y = (delta->y < 0) ? -1 : 1;
}

void	draw_line(t_fdf *ptr, t_point one, t_point two, int color)
{
	t_point		delta;
	t_point		s;
	double		slope;
	double		pitch;

	drawline_init(&delta, &s, one, two);
	slope = (fabs(delta.y) < fabs(delta.x)) ? delta.y / delta.x
		: delta.x / delta.y;
	pitch = (fabs(delta.y) < fabs(delta.x)) ? one.y - (slope * one.x)
		: one.x - (slope * one.y);
	if (fabs(delta.y) < fabs(delta.x))
		while ((int)round(one.x) != (int)round(two.x))
		{
			fill_pixel(ptr, color, (int)round(one.x),
					(int)lround((slope * one.x) + pitch));
			one.x += s.x;
		}
	else
		while ((int)round(one.y) != (int)round(two.y))
		{
			fill_pixel(ptr, color, (int)lround((slope * one.y) + pitch),
					(int)round(one.y));
			one.y += s.y;
		}
}
