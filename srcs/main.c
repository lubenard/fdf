/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:05:44 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/13 18:54:54 by lubenard         ###   ########.fr       */
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

	(void)argc;
	(void)argv;
	fdf = NULL;
	if (get_map(fdf, argc, argv) == 1)
		return (1);
	//init_mlx(fdf);
	//free_structs(fdf);
	//draw_map(fdf);
	return (0);
}
