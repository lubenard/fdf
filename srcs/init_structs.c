/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  init_structs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:05:44 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/18 12:23:46 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Init struct for fdf
*/

t_fdf		*init_fdf_structs(void)
{
	t_fdf	*fdf;

	if (!(fdf = malloc(sizeof(t_fdf)))
	|| !(fdf->map = malloc(sizeof(t_map)))
	|| !(fdf->mlx = malloc(sizeof(t_mlx))))
		return (NULL);
	fdf->mlx->mlx_ptr = NULL;
	fdf->mlx->mlx_win = NULL;
	fdf->mlx->img_ptr = NULL;
	fdf->mlx->data = NULL;
	fdf->mlx->bpp = 0;
	fdf->mlx->size_line = 0;
	fdf->mlx->endian = 0;
	fdf->map->last = NULL;
	fdf->map->lst = NULL;
	fdf->map->size = 0;
	fdf->map->line_size = 0;
	return (fdf);
}

/*
** Create new element of linked list
*/

t_map_lst	*create_new_elem(void)
{
	t_map_lst *elem;

	if (!(elem = malloc(sizeof(t_map_lst))))
		return (NULL);
	elem->x = 0;
	elem->y = 0;
	elem->alt = 0;
	elem->color = 0x00FFFFFF;
	elem->up = NULL;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}
