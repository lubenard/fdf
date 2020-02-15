/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  init_structs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:05:44 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/15 19:54:54 by lubenard         ###   ########.fr       */
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
	|| !(fdf->map = malloc(sizeof(t_map))))
		return (NULL);
	fdf->mlx_ptr = NULL;
	fdf->mlx_win = NULL;
	fdf->map->last = NULL;
	fdf->map->lst = NULL;
	fdf->map->size = 0;
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
	elem->up = NULL;
	elem->down = NULL;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}
