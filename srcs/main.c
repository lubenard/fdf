/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:05:44 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/16 16:40:20 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_structs(t_fdf *fdf)
{
	(void)fdf;
}

int		main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = NULL;
	if (get_map(&fdf, argc, argv) == 1 || init_mlx(fdf) == 1)
		return (1);
	//free_structs(fdf);
	//draw(fdf);
	return (0);
}
