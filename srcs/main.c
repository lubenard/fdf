/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:05:44 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/21 14:28:44 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = NULL;
	if (get_map(&fdf, argc, argv) == 1 || init_mlx(fdf) == 1)
		return (1);
	/*while (fdf->map->lst)
	{
		pai(fdf->map->lst);
		fdf->map->lst = fdf->map->lst->next;
	}*/
	draw(fdf);
	//free_structs(fdf);
	return (0);
}
